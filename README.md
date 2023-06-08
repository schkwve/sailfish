# Sailfish - Lightweight, Cross-Platform E-Mail Client

# So... what can it do?

As of now, Sailfish is in a very early stage of development. I'm working on implementing SMTP to _just work_. Then, security functions will come next, and the GUI last.

# Building

For testing purposes, one file was purposefully omitted: `src/utils/login.h`.
Create the file from the following template, and fill the defines appropriately:
```
#ifndef __LOGIN_H_
#define __LOGIN_H_

#define LOGIN_USERNAME "john.doe@something.net"
#define LOGIN_PASS "qwerty"

#endif // __LOGIN_H_
```

You'll also need wxWidgets installed *and* the `wx-config` command available.

To build Sailfish, simply run `make`. For more build options, run `make help`.

# Contributing

If you notice a bug, feel free to open an [Issue](https://github.com/schkwve/sailfish/issues).
Pull Requests are also welcome if they fix a bug or a security issue.

# License

![GPL3 License](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)

Sailfish is licensed under the GPL3 license, which you can find [here](LICENSE.md).