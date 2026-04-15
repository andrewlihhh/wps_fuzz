# How to build Foxit PDF SDK demo

* Please make sure you have the right environment configuration, and make sure you have cmake(3.1 and later) on your machine

    | OS    | Compiler tools or IDE | version          |
    | ----- | --------------------- | ---------------- |
    | Mac   | Xcode                 | 11.4.1 and later |
    | Linux | GCC                   | 4.9.4 and later  |

    And correctly configure the environment variables for the above tools.

* Following commands can be used to build demo(s):
    To build simple_demo:
    ```shell
    $ cmake -DPRJ_NAME=annotation
    $ make
    $ ./annotation_xxx
    ```
> The `PRJ_NAME` is the project name of simple_demo, 
> Currently, it must be `annotation` `attachment` `bookmark` `fdf` `form` `image2pdf` `page-organization` `pdf2image`
> `pdf2text` `pdfflatten` `watermark` and so on.
> The executabled file would be generated after executing of `make` command successfully, such as `annotation_xxx`, 
> The `xxx` means the architecture name.
> Before using this demo "security" or "signature", user should ensure that openssl environment has been prepared:
> user should ensure all the openssl header files included by "#include" can be found. And user should put the "libssl.a" and "libcrypto.a"
> in the directory "lib".
