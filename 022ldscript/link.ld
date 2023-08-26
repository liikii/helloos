SECTIONS {
    . = 0x1000; /* 程序的起始地址 */

    .data : {
        *(.data)
    }

    .text : {
        *(.text)
    }

    custom_section : {
        *(.custom_section)
    }
}
