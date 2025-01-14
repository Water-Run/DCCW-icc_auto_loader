# DCCW-icc_auto_loader  

## Introduction  

The default monitor color profile might not match your expectations (for instance, as someone accustomed to a 9300K color temperature, I find the typical 6500K warm color temperature intolerable).  
If your monitor does not provide direct adjustments, Windows offers `dccw` for manual software calibration. The calibration generates an `.icc` file and saves it in the system’s `Color Management` program’s default settings, which should automatically load when the device starts up.  
In most cases, this is sufficient—after a slight loss of brightness and a brief delay during startup, you can enjoy the calibrated pure white.  
However, this feature is prone to issues. Occasionally, the `.icc` file fails to load automatically.  
The DCCW-icc_auto_loader project provides a simple application that ensures the `.icc` file is loaded automatically at startup.  
This lightweight project is written in `C`, delivers a direct `.exe` file, and maintains compatibility with Windows.  

## User Guide  

### Generate a Color Profile Using DCCW  

> If you are already familiar with DCCW and know how to copy the generated `.icc` file, you can skip this section.  

1. Press the `Windows logo key` + `R` to open the Run dialog. Enter `dccw` and press Enter.  
2. Follow the steps in `dccw`, and adjust the red and green sliders under the `Adjust color balance` section to achieve the desired color temperature.  
3. After completing `dccw`, locate the generated `.icc` file and copy it. It should be in the directory:  
   `C:\Windows\System32\spool\drivers\color`  
   The filename will be `CalibratedDisplayProfile-[number].icc` (e.g., `CalibratedDisplayProfile-1.icc`). Select the file with the most recent modification date. You can also use software like `Everything` for quick searching.  

### Using D_ial (DCCW-icc_auto_loader)  

1. Copy the `.icc` file from the previous step to the same directory as `D_ial.exe`, and rename it to `D_ial.icc`.  
2. Right-click and run `D_ial.exe` as an administrator.  
   `D_ial` will automatically configure itself to start at boot and load the `D_ial.icc` file for the system.  

> If you do not run `D_ial` as an administrator, it may not function properly.  
>> To disable startup, you can adjust the settings via Settings (Windows 11), Task Manager (Windows 10), or `msconfig` (Windows 8 and earlier).  
