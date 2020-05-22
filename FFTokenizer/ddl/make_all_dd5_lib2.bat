@echo off
echo Foundation Fieldbus DD Standard Library
echo (c) 1996-2010 Fieldbus Foundation.  All rights reserved.
echo Revision:  3.60
echo Date:      30-Jul-2010
echo This will tokenize the complete library.

:PROMPT
echo Do you want to build the library with standard
echo no_download and upload_wanted collections (#define UD_LISTS)
set /p option=[y/n]?

IF %option%==y goto BUILD_UD
IF %option%==n goto BUILD
echo Invalid selection!
goto PROMPT

:BUILD_UD
pause Press ctrl-c to stop now; otherwise press a key to continue...

echo fftok -a -u -DLIB2 -DUD_LISTS aal_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O aal_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS adv_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O adv_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS adv_pvb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O adv_pvb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ahi_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ahi_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ai_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ai_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ao_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ao_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ar_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ar_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS bas_pvb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O bas_pvb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS bg_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O bg_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS calca_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O calca_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS calcd_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O calcd_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cao_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cao_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cdo_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cdo_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cmplx_xdcr_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cmplx_xdcr_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cs_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cs_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cust_calc_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cust_calc_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cust_cntrl_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cust_cntrl_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cust_in_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cust_in_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS cust_out_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O cust_out_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS dal_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O dal_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS dc_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O dc_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS dhi_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O dhi_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS di_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O di_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS do_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O do_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS dsc_pvb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O dsc_pvb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS dt_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O dt_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS flow_cb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O flow_cb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ft_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ft_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS  gen_xdcr_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS  -O gen_xdcr_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS is_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O is_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS it_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O it_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ll_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ll_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS mai.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O mai.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS mao.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O mao.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS mdi.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O mdi.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS mdo.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O mdo.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS mio_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O mio_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ml_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ml_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS os_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O os_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS pd_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O pd_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS pi_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O pi_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS pidblock.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O pidblock.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS pos_a_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O pos_a_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS pos_a_d_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O pos_a_d_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS pos_d_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O pos_d_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS press_cb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O press_cb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS press_cb2.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O press_cb2.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS prog_resblock.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O prog_resblock.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS ra_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O ra_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rdrl_cb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rdrl_cb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS resblock2.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O resblock2.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS resblock.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O resblock.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS sc_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O sc_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS sif_aiblock.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O sif_aiblock.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS sif_doblock.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O sif_doblock.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS sif_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O sif_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS sif_resblock.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O sif_resblock.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS spg_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O spg_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS spid_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O spid_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS std_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O std_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS temp_c2s.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O temp_c2s.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS temp_c2s2.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O temp_c2s2.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS temp_cb.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O temp_cb.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS temp_cb2.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O temp_cb2.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS tmr_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O tmr_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS xdcr_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O xdcr_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_mai16_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_mai16_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_mao16_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_mao16_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_mbi64_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_mbi64_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_mbo64_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_mbo64_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_assoc_prim_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_assoc_prim_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_assoc_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_assoc_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_xdcr_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_xdcr_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_hart_xdcr_parm.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_hart_xdcr_parm.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_hart_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_hart_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_wless_hart_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_wless_hart_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_vfd_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_vfd_block.ddl

echo fftok -a -u -DLIB2 -DUD_LISTS rio_h1_block.ddl
call fftok -a -u -DLIB2 -DUD_LISTS -O rio_h1_block.ddl

goto END

:BUILD
pause Press ctrl-c to stop now; otherwise press a key to continue...

echo fftok -a -u aal_block.ddl
call fftok -a -u -O aal_block.ddl

echo fftok -a -u adv_parm.ddl
call fftok -a -u -O adv_parm.ddl

echo fftok -a -u adv_pvb.ddl
call fftok -a -u -O adv_pvb.ddl

echo fftok -a -u ahi_block.ddl
call fftok -a -u -O ahi_block.ddl

echo fftok -a -u ai_block.ddl
call fftok -a -u -O ai_block.ddl

echo fftok -a -u ao_block.ddl
call fftok -a -u -O ao_block.ddl

echo fftok -a -u ar_block.ddl
call fftok -a -u -O ar_block.ddl

echo fftok -a -u bas_pvb.ddl
call fftok -a -u -O bas_pvb.ddl

echo fftok -a -u bg_block.ddl
call fftok -a -u -O bg_block.ddl

echo fftok -a -u calca_block.ddl
call fftok -a -u -O calca_block.ddl

echo fftok -a -u calcd_block.ddl
call fftok -a -u -O calcd_block.ddl

echo fftok -a -u cao_block.ddl
call fftok -a -u -O cao_block.ddl

echo fftok -a -u cdo_block.ddl
call fftok -a -u -O cdo_block.ddl

echo fftok -a -u cmplx_xdcr_block.ddl
call fftok -a -u -O cmplx_xdcr_block.ddl

echo fftok -a -u cs_block.ddl
call fftok -a -u -O cs_block.ddl

echo fftok -a -u cust_calc_block.ddl
call fftok -a -u -O cust_calc_block.ddl

echo fftok -a -u cust_cntrl_block.ddl
call fftok -a -u -O cust_cntrl_block.ddl

echo fftok -a -u cust_in_block.ddl
call fftok -a -u -O cust_in_block.ddl

echo fftok -a -u cust_out_block.ddl
call fftok -a -u -O cust_out_block.ddl

echo fftok -a -u dal_block.ddl
call fftok -a -u -O dal_block.ddl

echo fftok -a -u dc_block.ddl
call fftok -a -u -O dc_block.ddl

echo fftok -a -u dhi_block.ddl
call fftok -a -u -O dhi_block.ddl

echo fftok -a -u di_block.ddl
call fftok -a -u -O di_block.ddl

echo fftok -a -u do_block.ddl
call fftok -a -u -O do_block.ddl

echo fftok -a -u dsc_pvb.ddl
call fftok -a -u -O dsc_pvb.ddl

echo fftok -a -u dt_block.ddl
call fftok -a -u -O dt_block.ddl

echo fftok -a -u flow_cb.ddl
call fftok -a -u -O flow_cb.ddl

echo fftok -a -u ft_block.ddl
call fftok -a -u -O ft_block.ddl

echo fftok -a -u gen_xdcr_block.ddl
call fftok -a -u -O gen_xdcr_block.ddl

echo fftok -a -u is_block.ddl
call fftok -a -u -O is_block.ddl

echo fftok -a -u it_block.ddl
call fftok -a -u -O it_block.ddl

echo fftok -a -u ll_block.ddl
call fftok -a -u -O ll_block.ddl

echo fftok -a -u mai.ddl
call fftok -a -u -O mai.ddl

echo fftok -a -u mao.ddl
call fftok -a -u -O mao.ddl

echo fftok -a -u mdi.ddl
call fftok -a -u -O mdi.ddl

echo fftok -a -u mdo.ddl
call fftok -a -u -O mdo.ddl

echo fftok -a -u mio_parm.ddl
call fftok -a -u -O mio_parm.ddl

echo fftok -a -u ml_block.ddl
call fftok -a -u -O ml_block.ddl

echo fftok -a -u os_block.ddl
call fftok -a -u -O os_block.ddl

echo fftok -a -u pd_block.ddl
call fftok -a -u -O pd_block.ddl

echo fftok -a -u pi_block.ddl
call fftok -a -u -O pi_block.ddl

echo fftok -a -u pidblock.ddl
call fftok -a -u -O pidblock.ddl

echo fftok -a -u pos_a_block.ddl
call fftok -a -u -O pos_a_block.ddl

echo fftok -a -u pos_a_d_block.ddl
call fftok -a -u -O pos_a_d_block.ddl

echo fftok -a -u pos_d_block.ddl
call fftok -a -u -O pos_d_block.ddl

echo fftok -a -u press_cb.ddl
call fftok -a -u -O press_cb.ddl

echo fftok -a -u press_cb2.ddl
call fftok -a -u -O press_cb2.ddl

echo fftok -a -u prog_resblock.ddl
call fftok -a -u -O prog_resblock.ddl

echo fftok -a -u ra_block.ddl
call fftok -a -u -O ra_block.ddl

echo fftok -a -u rdrl_cb.ddl
call fftok -a -u -O rdrl_cb.ddl

echo fftok -a -u resblock2.ddl
call fftok -a -u -O resblock2.ddl

echo fftok -a -u resblock.ddl
call fftok -a -u -O resblock.ddl

echo fftok -a -u sc_block.ddl
call fftok -a -u -O sc_block.ddl

echo fftok -a -u sif_aiblock.ddl
call fftok -a -u -O sif_aiblock.ddl

echo fftok -a -u sif_doblock.ddl
call fftok -a -u -O sif_doblock.ddl

echo fftok -a -u sif_parm.ddl
call fftok -a -u -O sif_parm.ddl

echo fftok -a -u sif_resblock.ddl
call fftok -a -u -O sif_resblock.ddl

echo fftok -a -u spg_block.ddl
call fftok -a -u -O spg_block.ddl

echo fftok -a -u spid_block.ddl
call fftok -a -u -O spid_block.ddl

echo fftok -a -u std_parm.ddl
call fftok -a -u -O std_parm.ddl

echo fftok -a -u temp_c2s.ddl
call fftok -a -u -O temp_c2s.ddl

echo fftok -a -u temp_c2s2.ddl
call fftok -a -u -O temp_c2s2.ddl

echo fftok -a -u temp_cb.ddl
call fftok -a -u -O temp_cb.ddl

echo fftok -a -u temp_cb2.ddl
call fftok -a -u -O temp_cb2.ddl

echo fftok -a -u tmr_block.ddl
call fftok -a -u -O tmr_block.ddl

echo fftok -a -u xdcr_parm.ddl
call fftok -a -u -O xdcr_parm.ddl

echo fftok -a -u rio_parm.ddl
call fftok -a -u -O rio_parm.ddl

echo fftok -a -u rio_mai16_block.ddl
call fftok -a -u -O rio_mai16_block.ddl

echo fftok -a -u rio_mao16_block.ddl
call fftok -a -u -O rio_mao16_block.ddl

echo fftok -a -u rio_mbi64_block.ddl
call fftok -a -u -O rio_mbi64_block.ddl

echo fftok -a -u rio_mbo64_block.ddl
call fftok -a -u -O rio_mbo64_block.ddl

echo fftok -a -u rio_assoc_prim_block.ddl
call fftok -a -u -O rio_assoc_prim_block.ddl

echo fftok -a -u rio_assoc_block.ddl
call fftok -a -u -O rio_assoc_block.ddl

echo fftok -a -u rio_xdcr_parm.ddl
call fftok -a -u -O rio_xdcr_parm.ddl

echo fftok -a -u rio_hart_xdcr_parm.ddl
call fftok -a -u -O rio_hart_xdcr_parm.ddl

echo fftok -a -u rio_hart_block.ddl
call fftok -a -u -O rio_hart_block.ddl

echo fftok -a -u rio_wless_hart_block.ddl
call fftok -a -u -O rio_wless_hart_block.ddl

echo fftok -a -u rio_vfd_block.ddl
call fftok -a -u -O rio_vfd_block.ddl

echo fftok -a -u rio_h1_block.ddl
call fftok -a -u -O rio_h1_block.ddl

goto END

:END

ECHO DONE
