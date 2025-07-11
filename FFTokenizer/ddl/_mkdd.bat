echo BUILDING: C:\TFSSC\Projects\FW_SVI_FF_Releases\Release2\FD-SW-DeltaV\target\appl\fbif\ddl\svi_positioner.ddl
path=D:\FF\TOK\BIN;%path%
D:\FF\TOK\BIN\ff5pretok.exe -a  -z   -d "C:\FF\DDL\standard.dct" -I"C:\FF\DDL" -R "C:\FF\DDL\release" -p "C:\FF\DDL" "C:\TFSSC\Projects\FW_SVI_FF_Releases\Release2\FD-SW-DeltaV\target\appl\fbif\ddl\svi_positioner.ddl" _tmptok
call D:\FF\TOK\BIN\ff5_tok32.exe _tmptok
