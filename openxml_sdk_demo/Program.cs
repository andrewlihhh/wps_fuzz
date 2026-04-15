// See https://aka.ms/new-console-template for more information
using A = DocumentFormat.OpenXml.Drawing;
using DW = DocumentFormat.OpenXml.Drawing.Wordprocessing;
using PIC = DocumentFormat.OpenXml.Drawing.Pictures;
using System.Text.Json;
using DocumentFormat.OpenXml;
using DocumentFormat.OpenXml.Packaging;
using DocumentFormat.OpenXml.Wordprocessing;

if (args.Length < 2)
{
	Console.Error.WriteLine("Usage: dotnet run -- <input-ir.json> <output.docx>");
	return 1;
}

var inputPath = args[0];
var outputPath = args[1];

if (!File.Exists(inputPath))
{
	Console.Error.WriteLine($"IR file not found: {inputPath}");
	return 2;
}

var options = new JsonSerializerOptions
{
	PropertyNameCaseInsensitive = true,
};

var ir = JsonSerializer.Deserialize<DocxIr>(File.ReadAllText(inputPath), options);
if (ir is null)
{
	Console.Error.WriteLine("Failed to deserialize IR JSON.");
	return 3;
}

Directory.CreateDirectory(Path.GetDirectoryName(Path.GetFullPath(outputPath)) ?? ".");
BuildDocx(ir, outputPath);
Console.WriteLine($"Generated DOCX: {outputPath}");
return 0;

static void BuildDocx(DocxIr ir, string outputPath)
{
	if (File.Exists(outputPath))
	{
		File.Delete(outputPath);
	}

	using var wordDocument = WordprocessingDocument.Create(outputPath, WordprocessingDocumentType.Document);
	var mainPart = wordDocument.AddMainDocumentPart();
	mainPart.Document = new Document(new Body());

	AddStyleDefinitions(mainPart);
	AddNumberingDefinitions(mainPart);

	var body = mainPart.Document.Body ?? throw new InvalidOperationException("Document body was not created.");

	if (!string.IsNullOrWhiteSpace(ir.Title))
	{
		body.Append(CreateParagraph(ir.Title, "Title"));
	}

	foreach (var block in ir.Blocks)
	{
		AppendBlock(mainPart, body, block);
	}

	body.Append(new SectionProperties(
		new PageSize { Width = 11906U, Height = 16838U },
		new PageMargin { Top = 1440, Right = 1440U, Bottom = 1440, Left = 1440U, Header = 708U, Footer = 708U, Gutter = 0U }
	));

	mainPart.Document.Save();
}

static void AppendBlock(MainDocumentPart mainPart, Body body, IrBlock block)
{
	switch (block.Type?.ToLowerInvariant())
	{
		case "paragraph":
			body.Append(CreateParagraph(block.Text ?? string.Empty, block.Style ?? "Normal"));
			break;
		case "list":
			foreach (var item in block.Items)
			{
				body.Append(CreateListParagraph(item, block.ListStyle ?? "ListNumber", block.NumId ?? 1));
			}
			break;
		case "table":
			body.Append(CreateTable(block.Rows));
			break;
		case "hyperlink":
			body.Append(CreateHyperlinkParagraph(mainPart, block.Text ?? string.Empty, block.Url ?? "https://example.com", block.Style ?? "Normal"));
			break;
		case "image":
			body.Append(CreateImageParagraph(mainPart, block.AltText ?? "embedded image"));
			break;
		default:
			body.Append(CreateParagraph($"[unsupported block type: {block.Type}]", "Normal"));
			break;
	}
}

static Paragraph CreateHyperlinkParagraph(MainDocumentPart mainPart, string text, string url, string styleId)
{
	Uri hyperlinkUri;
	if (!Uri.TryCreate(url, UriKind.Absolute, out hyperlinkUri))
	{
		hyperlinkUri = new Uri("https://example.com", UriKind.Absolute);
	}

	var relationship = mainPart.AddHyperlinkRelationship(hyperlinkUri, true);
	return new Paragraph(
		new ParagraphProperties(new ParagraphStyleId { Val = styleId }),
		new Hyperlink(
			new Run(
				new RunProperties(new RunStyle { Val = "Hyperlink" }),
				new Text(text) { Space = SpaceProcessingModeValues.Preserve }
			)
		)
		{
			Id = relationship.Id,
			History = OnOffValue.FromBoolean(true)
		}
	);
}

static Paragraph CreateImageParagraph(MainDocumentPart mainPart, string altText)
{
	var imagePart = mainPart.AddImagePart(ImagePartType.Png);
	using (var stream = new MemoryStream(GetTinyPngBytes()))
	{
		imagePart.FeedData(stream);
	}

	var relationshipId = mainPart.GetIdOfPart(imagePart);
	var drawingId = (uint)Math.Abs(Guid.NewGuid().GetHashCode());
	if (drawingId == 0)
	{
		drawingId = 1;
	}
	return new Paragraph(new Run(CreateImageDrawing(relationshipId, drawingId, altText)));
}

static byte[] GetTinyPngBytes()
{
	return Convert.FromBase64String("iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAIAAACQd1PeAAAADElEQVR4nGP4z8AAAAQAAQUBAO7/EQAAAABJRU5ErkJggg==");
}

static Drawing CreateImageDrawing(string relationshipId, uint drawingId, string altText)
{
	return new Drawing(
		new DW.Inline(
			new DW.Extent { Cx = 190500L, Cy = 190500L },
			new DW.EffectExtent
			{
				LeftEdge = 0L,
				TopEdge = 0L,
				RightEdge = 0L,
				BottomEdge = 0L,
			},
			new DW.DocProperties { Id = drawingId, Name = $"Picture {drawingId}", Description = altText },
			new DW.NonVisualGraphicFrameDrawingProperties(new A.GraphicFrameLocks { NoChangeAspect = true }),
			new A.Graphic(
				new A.GraphicData(
					new PIC.Picture(
						new PIC.NonVisualPictureProperties(
							new PIC.NonVisualDrawingProperties { Id = 0U, Name = $"image-{drawingId}.png" },
							new PIC.NonVisualPictureDrawingProperties()
						),
						new PIC.BlipFill(
							new A.Blip { Embed = relationshipId },
							new A.Stretch(new A.FillRectangle())
						),
						new PIC.ShapeProperties(
							new A.Transform2D(
								new A.Offset { X = 0L, Y = 0L },
								new A.Extents { Cx = 190500L, Cy = 190500L }
							),
							new A.PresetGeometry(new A.AdjustValueList()) { Preset = A.ShapeTypeValues.Rectangle }
						)
					)
				)
				{ Uri = "http://schemas.openxmlformats.org/drawingml/2006/picture" }
			)
		)
		{
			DistanceFromTop = 0U,
			DistanceFromBottom = 0U,
			DistanceFromLeft = 0U,
			DistanceFromRight = 0U,
			EditId = "50D07946"
		}
	);
}

static Paragraph CreateParagraph(string text, string styleId)
{
	return new Paragraph(
		new ParagraphProperties(new ParagraphStyleId { Val = styleId }),
		new Run(new Text(text) { Space = SpaceProcessingModeValues.Preserve })
	);
}

static Paragraph CreateListParagraph(string text, string styleId, int numId)
{
	return new Paragraph(
		new ParagraphProperties(
			new ParagraphStyleId { Val = styleId },
			new NumberingProperties(
				new NumberingLevelReference { Val = 0 },
				new NumberingId { Val = numId }
			)
		),
		new Run(new Text(text) { Space = SpaceProcessingModeValues.Preserve })
	);
}

static Table CreateTable(List<List<string>> rows)
{
	var table = new Table();
	table.AppendChild(new TableProperties(
		new TableStyle { Val = "TableGrid" },
		new TableWidth { Width = "0", Type = TableWidthUnitValues.Auto },
		new TableBorders(
			new TopBorder { Val = BorderValues.Single, Size = 4 },
			new BottomBorder { Val = BorderValues.Single, Size = 4 },
			new LeftBorder { Val = BorderValues.Single, Size = 4 },
			new RightBorder { Val = BorderValues.Single, Size = 4 },
			new InsideHorizontalBorder { Val = BorderValues.Single, Size = 4 },
			new InsideVerticalBorder { Val = BorderValues.Single, Size = 4 }
		)
	));

	foreach (var row in rows)
	{
		var tr = new TableRow();
		foreach (var cellText in row)
		{
			tr.Append(new TableCell(
				new Paragraph(new Run(new Text(cellText) { Space = SpaceProcessingModeValues.Preserve })),
				new TableCellProperties(new TableCellWidth { Type = TableWidthUnitValues.Auto })
			));
		}

		table.Append(tr);
	}

	return table;
}

static void AddStyleDefinitions(MainDocumentPart mainPart)
{
	var stylePart = mainPart.AddNewPart<StyleDefinitionsPart>();
	stylePart.Styles = new Styles(
		new DocDefaults(
			new RunPropertiesDefault(
				new RunPropertiesBaseStyle(
					new RunFonts { AsciiTheme = ThemeFontValues.MinorHighAnsi, HighAnsiTheme = ThemeFontValues.MinorHighAnsi },
					new FontSize { Val = "22" },
					new FontSizeComplexScript { Val = "22" }
				)
			),
			new ParagraphPropertiesDefault()
		),
		CreateParagraphStyle("Normal", "Normal"),
		CreateParagraphStyle("Title", "Title", true, "40"),
		CreateParagraphStyle("Heading1", "Heading 1", true, "32"),
		CreateParagraphStyle("ListNumber", "List Number"),
		CreateParagraphStyle("ListBullet", "List Bullet"),
		CreateParagraphStyle("ListAlpha", "List Alpha"),
		CreateHyperlinkStyle(),
		CreateTableStyle()
	);
	stylePart.Styles.Save();
}

static Style CreateParagraphStyle(string styleId, string styleName, bool bold = false, string? size = null)
{
	var style = new Style { Type = StyleValues.Paragraph, StyleId = styleId };
	style.Append(new StyleName { Val = styleName });
	style.Append(new BasedOn { Val = "Normal" });
	style.Append(new UIPriority { Val = 1 });
	style.Append(new PrimaryStyle());

	var runProps = new StyleRunProperties();
	runProps.Append(new RunFonts { AsciiTheme = ThemeFontValues.MinorHighAnsi, HighAnsiTheme = ThemeFontValues.MinorHighAnsi });
	if (bold)
	{
		runProps.Append(new Bold());
		runProps.Append(new RunFonts { AsciiTheme = ThemeFontValues.MajorHighAnsi, HighAnsiTheme = ThemeFontValues.MajorHighAnsi });
	}
	if (size is not null)
	{
		runProps.Append(new FontSize { Val = size });
	}

	style.Append(runProps);

	if (styleId.StartsWith("List", StringComparison.Ordinal))
	{
		style.Append(new StyleParagraphProperties(new Indentation { Left = "720" }));
	}

	return style;
}

static Style CreateHyperlinkStyle()
{
	var style = new Style { Type = StyleValues.Character, StyleId = "Hyperlink", CustomStyle = true };
	style.Append(new StyleName { Val = "Hyperlink" });
	style.Append(new BasedOn { Val = "DefaultParagraphFont" });
	style.Append(new UIPriority { Val = 99 });
	style.Append(new UnhideWhenUsed());
	style.Append(new StyleRunProperties(new Color { ThemeColor = ThemeColorValues.Hyperlink }, new Underline { Val = UnderlineValues.Single }));
	return style;
}

static Style CreateTableStyle()
{
	var style = new Style { Type = StyleValues.Table, StyleId = "TableGrid" };
	style.Append(new StyleName { Val = "Table Grid" });
	style.Append(new StyleTableProperties(
		new TableBorders(
			new TopBorder { Val = BorderValues.Single, Size = 4 },
			new BottomBorder { Val = BorderValues.Single, Size = 4 },
			new LeftBorder { Val = BorderValues.Single, Size = 4 },
			new RightBorder { Val = BorderValues.Single, Size = 4 },
			new InsideHorizontalBorder { Val = BorderValues.Single, Size = 4 },
			new InsideVerticalBorder { Val = BorderValues.Single, Size = 4 }
		)
	));
	return style;
}

static void AddNumberingDefinitions(MainDocumentPart mainPart)
{
	var numberingPart = mainPart.AddNewPart<NumberingDefinitionsPart>();
	numberingPart.Numbering = new Numbering(
		CreateAbstractNumbering(0, NumberFormatValues.Decimal, "%1.", "ListNumber"),
		CreateAbstractNumbering(1, NumberFormatValues.Bullet, "•", "ListBullet"),
		CreateAbstractNumbering(2, NumberFormatValues.LowerLetter, "%1)", "ListAlpha"),
		new NumberingInstance(new AbstractNumId { Val = 0 }) { NumberID = 1 },
		new NumberingInstance(new AbstractNumId { Val = 1 }) { NumberID = 2 },
		new NumberingInstance(new AbstractNumId { Val = 2 }) { NumberID = 3 }
	);
	numberingPart.Numbering.Save();
}

static AbstractNum CreateAbstractNumbering(int abstractNumId, NumberFormatValues format, string levelText, string styleId)
{
	return new AbstractNum(
		new MultiLevelType { Val = MultiLevelValues.SingleLevel },
		new Level(
			new StartNumberingValue { Val = 1 },
			new NumberingFormat { Val = format },
			new LevelText { Val = levelText },
			new LevelJustification { Val = LevelJustificationValues.Left },
			new ParagraphStyleIdInLevel { Val = styleId },
			new PreviousParagraphProperties(new Indentation { Left = "720", Hanging = "360" })
		) { LevelIndex = 0 }
	) { AbstractNumberId = abstractNumId };
}

sealed class DocxIr
{
	public string? Title { get; set; }
	public List<IrBlock> Blocks { get; set; } = [];
}

sealed class IrBlock
{
	public string? Type { get; set; }
	public string? Style { get; set; }
	public string? Text { get; set; }
	public string? Url { get; set; }
	public string? AltText { get; set; }
	public string? ListStyle { get; set; }
	public int? NumId { get; set; }
	public List<string> Items { get; set; } = [];
	public List<List<string>> Rows { get; set; } = [];
}
