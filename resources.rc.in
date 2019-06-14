#include <winuser.h>
#include <winnt.h>

LANGUAGE 25,1

STRINGTABLE LANGUAGE LANG_NEUTRAL, SUBLANG_NEUTRAL
BEGIN
        1 "@PROJECT_NAME@"
END
//IDI_ICON1       ICON    DISCARDABLE     "icon.ico"
//IDR_APP_ICON    ICON                    "icon.ico"

1 VERSIONINFO
        FILEVERSION    @PROJECT_VERSION_MAJOR@,@PROJECT_VERSION_MINOR@,@PROJECT_VERSION_PATCH@,@PROJECT_VERSION_TWEAK@
        PRODUCTVERSION @PROJECT_VERSION_MAJOR@,@PROJECT_VERSION_MINOR@,@PROJECT_VERSION_PATCH@,@PROJECT_VERSION_TWEAK@
        FILEOS         0x00000000
        FILETYPE       0x00000001
BEGIN
        BLOCK "StringFileInfo"
        BEGIN
          BLOCK "040904e4"
          BEGIN
            VALUE "Comments",           "\0"
            VALUE "CompanyName",        "\0"
            VALUE "FileDescription",    "\0"
            VALUE "FileVersion",        "@PROJECT_VERSION@\0"
            VALUE "InternalName",       "@PROJECT_NAME@\0"
            VALUE "LegalCopyright",     "\0"
            VALUE "LegalTrademarks",    "\0"
            VALUE "OriginalFilename",   ""
            VALUE "ProductName",        "@PROJECT_NAME@\0"
            VALUE "ProductVersion",     "@PROJECT_VERSION@\0"
          END
        END
        BLOCK "VarFileInfo"
        BEGIN
            VALUE "Translation",        0x0419, 0x04E3
        END
END
