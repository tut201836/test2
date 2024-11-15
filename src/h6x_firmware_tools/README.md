# h6x_firmware_tools
GUI tools for HarvestX firmware configuration and performance testing.

## build and run

```bash
TARGET_DIR=${HOME}/ws_firmware_tools/

mkdir -p ${TARGET_DIR}/src
cd ${TARGET_DIR}/src/
git clone https://github.com/HarvestX/h6x_firmware_tools.git -b tmp/cart_firmware
cd ..

vcs import src/ < ./src/h6x_firmware_tools/build_depends.repos
source /opt/ros/humble/setup.bash

colcon build

# --- 実行 ---
source ${TARGET_DIR}/install/setup.bash
ros2 run xv3cart_tester_interface xv3cart_tester_interface
```
