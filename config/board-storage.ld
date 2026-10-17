SECTIONS
{
  .dxball_board ALIGN(8) (NOLOAD) :
  {
    KEEP(*(SORT_BY_NAME(.dxb.*)))
  }
}
INSERT AFTER .bss;
