import qbs

CppApplication {
    consoleApplication: true
    files: [
        "README.md",
        "COPYING.GPLv3.txt",
        "main.c",
        "pcf8574t_i2c.c",
        "pcf8574t_i2c.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
