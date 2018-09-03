azordx-cli
==========



[![oclif](https://img.shields.io/badge/cli-oclif-brightgreen.svg)](https://oclif.io)
[![Version](https://img.shields.io/npm/v/azordx-cli.svg)](https://npmjs.org/package/azordx-cli)
[![CircleCI](https://circleci.com/gh/VincentViet/azordx-cli/tree/master.svg?style=shield)](https://circleci.com/gh/VincentViet/azordx-cli/tree/master)
[![Appveyor CI](https://ci.appveyor.com/api/projects/status/github/VincentViet/azordx-cli?branch=master&svg=true)](https://ci.appveyor.com/project/VincentViet/azordx-cli/branch/master)
[![Codecov](https://codecov.io/gh/VincentViet/azordx-cli/branch/master/graph/badge.svg)](https://codecov.io/gh/VincentViet/azordx-cli)
[![Downloads/week](https://img.shields.io/npm/dw/azordx-cli.svg)](https://npmjs.org/package/azordx-cli)
[![License](https://img.shields.io/npm/l/azordx-cli.svg)](https://github.com/VincentViet/azordx-cli/blob/master/package.json)

<!-- toc -->
* [Usage](#usage)
* [Commands](#commands)
<!-- tocstop -->
# Usage
<!-- usage -->
```sh-session
$ npm install -g azordx-cli
$ azordx COMMAND
running command...
$ azordx (-v|--version|version)
azordx-cli/1.0.0 win32-x64 node-v8.11.4
$ azordx --help [COMMAND]
USAGE
  $ azordx COMMAND
...
```
<!-- usagestop -->
# Commands
<!-- commands -->
* [`azordx new [ProjectName]`](#azordx-hello-file)
* [`azordx help [COMMAND]`](#azordx-help-command)

## `azordx new [PROJECT NAME]`

describe the command here

```
USAGE
  $ azordx new [projectName]

OPTIONS
  -h, --help       show CLI help
  
EXAMPLE
  $ azordx new MyGame
```

_See code: [src\commands\new.ts](https://github.com/VincentViet/azordx-cli/v1.0.0/src\commands\new.ts)_

## `azordx help [COMMAND]`

display help for azordx

```
USAGE
  $ azordx help [COMMAND]

ARGUMENTS
  COMMAND  command to show help for

OPTIONS
  --all  see all commands in CLI
```

_See code: [@oclif/plugin-help](https://github.com/oclif/plugin-help/blob/v2.1.1/src\commands\help.ts)_
<!-- commandsstop -->
