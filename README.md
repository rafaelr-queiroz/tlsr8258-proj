# TLSR8258-PROJ

This is a repository that serves as a starting point to develop a new application based on the MCU **TLSR8258** from Telink. The repository contains a template project based on **TLSR8258DK48** development board, which is powered with the **TLSR8258F512ET48** microncontroller. The template project is the usual _Hello World_ for embedded systems, i.e.: a Blink LED example

## Environment

By the time this template project was developed, the following tools/software were used:

- **Telink IoT Studio V2025.2** - This is the IDE used to develop IoT applications for MCUs from Telink. It can be downloaded from Telink's website:
    - [Telink IoT Studio (Windows)](https://doc.telink-semi.cn/tools/telink_iot_studio/TelinkIoTStudio_V2025.2.zip)
    - [Telink IoT Studio (Linux)](https://doc.telink-semi.cn/tools/telink_iot_studio/Telink_IoT_Studio_2025.2_Installer.run)
- **tc32-elf-gcc version 4.5.1-tc32-1.3** - Compiler used to build the code, installed together with Telink IoT Studio 2025.2
- **tc_platform_sdk-3.3.0** - This is the SDK (_Software Development Kit_) provided from Telink to be used with a variety of chips, including the TLSR8258. The SDK contains drivers to access peripherals, MCU clock configuration and runtime initialization, so the developer can really focus on the application. The template project uses this SDK as a starting point and keeps its original structure, so it is easier to bring any SDK updates from Telink in the future. One does not need to get the standalone SDK in order to use the template provided by this repository, but it can be cloned or downloaded:
    - [SDK repository](https://github.com/telink-semi/tc_platform_sdk)
    - [SDK single zip (V3.3.0)](https://github.com/telink-semi/tc_platform_sdk/archive/refs/tags/V3.3.0.zip)

## Building the project

1. Clone this repository. 
2. After launching Telink IoT Studio, go to _File_ --> _Import_
![alt text](images/file-import.png)
3. In _General_, select _Existing Projects into Workspace_ and click on _Next_
![alt text](images/export-into-ws.png)
4. Specify the path to where this repository was cloned, select the project to be imported and click on _Finish_
![alt text](images/select-proj.png)