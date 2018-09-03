azordx-cli
==========

<!-- toc -->
* [Prerequisite](#prerequisite)
* [Usage](#usage)
* [Commands](#commands)
<!-- tocstop -->

# Prerequisite
<!-- prerequisite -->
* Install [mingw-w64 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/rubenvb/)
**Or**
[mingw-w64 64-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/rubenvb/)
* Install [CMake](https://cmake.org/download/)
* Install [NodeJs](https://nodejs.org/en/)
* Make sure add them to your PATH
<!-- prerequisitestop -->

# Install
<!-- usage -->
* Clone this repo
* Run your cmd.exe, and cd to azordx-cli folder
* Then type:
```sh-session
$ npm link
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

_See code: [src\commands\new.ts](https://github.com/VincentViet/azordx-cli/blob/master/src/commands/new.ts)_

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
