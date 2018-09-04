import {Command} from '@oclif/command'
import fs = require('fs')
import inquirer = require('inquirer')
import path = require('path')

export default class New extends Command {
  static description = `create new AzorDx Project
  \ncreate new AzorDx Project`

  static hidden = false

  static usage = "new 'project name'"

  static examples = [
    '$ azordx new MyGame'
  ]

  static args = [
    {
      name: 'projectName',
      required: true,
      description: 'your project name',
      hidden: false,
      default: 'MyGame'
    }
  ]

  async run() {
    const {args} = this.parse(New)
    // global.console.log(args.projectName)
    let rootSourceDir = path.normalize(path.join(__dirname, '../../AzorDx'))
    let rootDir: string = path.join(global.process.cwd(), args.projectName)
    let responses = await inquirer.prompt([{
      name: 'compilerPath',
      message: 'Tell me where your compiler is (mingw32-g++.exe or g++.exe)',
      type: 'input',
    },
    {
      name: 'debuggerPath',
      message: 'Where is your debugger (gdb.exe)',
      type: 'input'
    }])

    fs.readdir(rootSourceDir, 'utf-8', (rootErr: any, dirs: any) => {
      if (rootErr) throw rootErr
      fs.mkdir(rootDir, (clondErr: any) => {
        if (clondErr) throw clondErr
        this.log(`created ${rootDir}`)
        dirs.forEach((dir: any) => {
          let sourceDir = path.join(rootSourceDir, dir)
          let destDir = path.join(rootDir, dir)

          switch (dir) {
            case '.vscode':
            case 'dll':
            case 'lib':
            case 'src':
              fs.mkdir(destDir, (subdirErr: any) => {
                if (subdirErr) throw subdirErr
                this.log(`created ${destDir}`)
                fs.readdir(sourceDir, 'utf-8', (err: any, files: any) => {
                  if (err) throw err
                  files.forEach((file: any) => {
                    let sourceFile = path.join(sourceDir, file)
                    let destFile = path.join(destDir, file)

                    switch (file) {
                      case 'launch.json':
                        fs.readFile(sourceFile, 'utf-8', (fileErr, data) => {
                          if (fileErr) throw fileErr
                          let obj = JSON.parse(data)
                          obj.configurations[0].program = '\${workspaceFolder}/bin/' + args.projectName + '.exe'
                          obj.configurations[0].miDebuggerPath = responses.debuggerPath
                          let objString = JSON.stringify(obj, null, 4)
                          fs.writeFile(destFile, objString, writeFileErr => {
                            if (writeFileErr) throw writeFileErr
                            this.log(`created ${destFile}`)
                          })
                        })
                        break

                      case 'c_cpp_properties.json':
                        fs.readFile(sourceFile, 'utf-8', (fileErr, data) => {
                          if (fileErr) throw fileErr
                          let obj = JSON.parse(data)
                          obj.configurations[0].compilerPath = responses.compilerPath
                          let objString = JSON.stringify(obj, null, 4)
                          fs.writeFile(destFile, objString, writeFileErr => {
                            if (writeFileErr) throw writeFileErr
                            this.log(`created ${destFile}`)
                          })
                        })
                        break

                      default:
                        fs.createReadStream(sourceFile).pipe(fs.createWriteStream(destFile))
                        this.log(`created ${destFile}`)
                    }
                  })
                })
              })
              break

            case 'include':
              fs.mkdir(destDir, (subdirErr: any) => {
                if (subdirErr) throw subdirErr
                this.log(`created ${destDir}`)

                fs.readdir(sourceDir, 'utf8', (includeErr, includeDirs) => {
                  if (includeErr) throw includeErr
                  includeDirs.forEach((includeDir: any) => {
                    let includeSource = path.join(sourceDir, includeDir)
                    let includeDest = path.join(destDir, includeDir)

                    fs.mkdir(includeDest, includeDestErr => {
                      if (includeDestErr) throw includeDestErr
                      this.log(`created ${includeDest}`)

                      fs.readdir(includeSource, (err, files) => {
                        if (err) throw err
                        files.forEach((file: any) => {
                          let sourceFile = path.join(includeSource, file)
                          let destFile = path.join(includeDest, file)
                          fs.createReadStream(sourceFile).pipe(fs.createWriteStream(destFile))
                          this.log(`created ${destFile}`)
                        })
                      })
                    })
                  })
                })
              })
              break

            case 'resources':
              fs.mkdir(destDir, subdirErr => {
                if (subdirErr) throw subdirErr
                this.log(`created ${destDir}`)
                fs.readdir(sourceDir, 'utf-8', (resourcesErr, resourcesDirs) => {
                  if (resourcesErr) throw resourcesErr

                  for (const resourcesDir of resourcesDirs) {
                    if (typeof resourcesDir === 'string') {
                      let resourcesDest = path.join(destDir, resourcesDir)
                      fs.mkdir(resourcesDest, mkErr => {
                        if (mkErr) throw mkErr
                        this.log(`created ${resourcesDest}`)
                      })
                    }
                  }
                })
              })
              break

            case '.config':
              fs.readFile(sourceDir, 'utf-8', (configErr, configData) => {
                if (configErr) throw configErr
                let obj = JSON.parse(configData)
                obj.windowTitle = args.projectName
                let objString = JSON.stringify(obj, null, 4)
                fs.writeFile(destDir, objString, writeFileErr => {
                  if (writeFileErr) throw writeFileErr
                  this.log(`created ${destDir}`)
                })
              })
              break

            case 'CMakeLists.txt':
              let cmakeData = `
cmake_minimum_required(VERSION 3.0)
project(${args.projectName})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/bin)

include_directories("\${PROJECT_SOURCE_DIR}/include")

file(GLOB SRC_FILES "\${PROJECT_SOURCE_DIR}/src/*.cc")
file(GLOB AZOR_SRC_FILES "\${PROJECT_SOURCE_DIR}/include/AzorDx/*.cc")
file(GLOB LIB_FILES "\${PROJECT_SOURCE_DIR}/lib/*.a")
file(GLOB DLL_FILES "\${PROJECT_SOURCE_DIR}/dll/*.dll")
file(GLOB TEXTURE_FILES "\${PROJECT_SOURCE_DIR}/resources/textures/*.*")
file(GLOB SOUND_FILES "\${PROJECT_SOURCE_DIR}/resources/sounds/*.*")
file(MAKE_DIRECTORY "\${PROJECT_SOURCE_DIR}/bin/resources")
file(MAKE_DIRECTORY "\${PROJECT_SOURCE_DIR}/bin/resources/sounds")
file(MAKE_DIRECTORY "\${PROJECT_SOURCE_DIR}/bin/resources/textures")
file(MAKE_DIRECTORY "\${PROJECT_SOURCE_DIR}/bin/resources/fonts")

#copy dlls
foreach(dll_file \${DLL_FILES})
    configure_file(\${dll_file} \${PROJECT_SOURCE_DIR}/bin COPYONLY)
endforeach(dll_file)

#copy textures
foreach(texture_file \${TEXTURE_FILES})
    configure_file(\${texture_file} \${PROJECT_SOURCE_DIR}/bin/resources/textures COPYONLY)
endforeach(texture_file)

#copy sounds
foreach(sound_file \${SOUND_FILES})
    configure_file(\${sound_file} \${PROJECT_SOURCE_DIR}/bin/resources/sounds COPYONLY)
endforeach(sound_file)

#copy .config
configure_file("\${PROJECT_SOURCE_DIR}/.config" "\${PROJECT_SOURCE_DIR}/bin" COPYONLY)

add_executable(${args.projectName} \${SRC_FILES} \${AZOR_SRC_FILES})
#add_library(${args.projectName} STATIC \${SRC_FILES})
target_link_libraries(${args.projectName} "libd3d9.a" "libd3dx9.a" "libwinmm.a" "libdxerr9.a" "libdxguid.a" "libdinput8.a"\${LIB_FILES})`

              fs.writeFile(destDir, cmakeData, writeCmakeErr => {
                if (writeCmakeErr) throw writeCmakeErr
                this.log(`created ${destDir}`)
              })
              break

            default:
              fs.createReadStream(sourceDir).pipe(fs.createWriteStream(destDir))

          }
        })
      })
    })
  }
}
