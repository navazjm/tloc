# TLOC - Total Lines of Code

## Table of Contents
- [Quick Start](#quick-start)
- [Overview](#overview)
- [License](#license)
- [Install](#install)
- [Usage](#usage)
    - [Options](#options)
- [Supported Languages](#supported-languages)
- [Contributing](#contributing)

## Quick Start

## Overview

## License

## Install

## Usage

### Options

```sh 
$ tloc --help
USAGE: tloc optional/path/ [options]

OPTIONAL PATH:

* Can be a path to a directory or a specific file
* Will default to CWD, if one of the following conditions is met:
    1. Omitted
    2. Path does not exist
    3. Do not have read access permisions
    4. Not provided as the second command-line arg.

META OPTIONS:
    -h, --help                      Display list of command-line options.
    -v, --version                   Display version of tloc.
    -sl, --supported-languages      Display a list of supported programming languages.

FILTERING AND SORTING OPTIONS:
    -iu, --include-untracked        Include files not being tracked by Git.

DISPLAY OPTIONS:
    -l, --language                  List data by programming languages, not by files.

```

For detailed usage instructions, checkout [options.md](./docs/options.md)

## Supported Languages

```sh 
$ tloc -sl
----------------------------------
Language             Extensions
----------------------------------
C                    c
C/C++ Header         h, hpp
C++                  cpp
Markdown             md
JavaScript           js
TypeScript           ts
```

Interested in adding a new language? Start a [discussion](https://github.com/navazjm/tloc/discussions),
and we can work together to incorporate it into tloc!

## Contributing 

Want to contribute to tloc? Awesome, we would love your input ♥\
\
If you have a feature request, start a [discussion](https://github.com/navazjm/tloc/discussions),
and we can work together to incorporate it into tloc!\
\
Encountered a defect? Please report it under [issues](https://github.com/navazjm/tloc/issues).
Be sure to include detailed information to help us address the issue effectively.\
\
Want to implement a feature request or fix a defect? Checkout our [contributing guide](./docs/contributing.md).

