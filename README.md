# Sailfish - Lightweight, Cross-Platform E-Mail Client

# So... what can it do?

As of now, Sailfish is in a very early stage of development. I'm working on implementing SMTP to _just work_. Then, security functions will come next, and the GUI last.

# Building

For testing purposes, one file was purposefully omitted: `src/utils/login.h`.
Create the file from the following template, and fill the defines appropriately:
```
#ifndef __LOGIN_H_
#define __LOGIN_H_

#define XOAUTH2_USER ""
#define XOAUTH2_ACCESS_TOKEN ""

#endif // __LOGIN_H_
```
`XOAUTH2_USER` contains the user's Google email address (e.g. `someuser@gmail.com`)
`XOAUTH2_ACCESS_TOKEN` can be created by following [this](https://alpineapp.email/alpine/alpine-info/misc/RegisteringAlpineinGmail.html) guide.

To build Sailfish, simply run `make`. For more build options, run `make help`.

# Running

To run Sailfish for testing, you'll need to run a test SMTP server first.
Make sure you have `docker` installed, and run the following command:
```
docker run --rm -it -p 3000:80 -p 2525:25 rnwood/smtp4dev:v3
```
After the server has loaded, run Sailfish by invoking `./sailfish`.

# Contributing

If you notice a bug, feel free to open an [Issue](https://github.com/schkwve/sailfish/issues).
Pull Requests are also welcome if they fix a bug or a security issue.

# License

![GPL3 License](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)

Sailfish is licensed under the GPL3 license, which you can find [here](LICENSE.md).