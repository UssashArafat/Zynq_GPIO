# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Projects\SOC_Projects\Counter_LedSwitch_Zedboard\ZynqSystem_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Projects\SOC_Projects\Counter_LedSwitch_Zedboard\ZynqSystem_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {ZynqSystem_wrapper}\
-hw {D:\Projects\SOC_Projects\Counter_LedSwitch_Zedboard\ZynqSystem_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {D:/Projects/SOC_Projects/Counter_LedSwitch_Zedboard}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {ZynqSystem_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
platform active {ZynqSystem_wrapper}
bsp reload
domain active {zynq_fsbl}
bsp reload
