#include "xv3cart_firmware_mock/xv3cart_firmware_mock.hpp"


int main(int argc, char ** argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
    return 1;
  }
  std::string port = argv[1];
  auto interface = std::make_shared<xv3cart_firmware_mock::Xv3CartFirmwareMock>(port, 115200);
  interface->rx_tof_packet_ = std::make_unique<xv3cart_firmware_mock::RxToFPacket>();
  interface->rx_whl_packet_ = std::make_unique<xv3cart_firmware_mock::RxWhlPacket>();
  interface->rx_info_packet_ = std::make_unique<xv3cart_firmware_mock::RxInfoPacket>();
  interface->rx_trigger1_packet_ = std::make_unique<xv3cart_firmware_mock::RxTrigger1Packet>();

  interface->configure();
  interface->activate();

  while (true) {
    interface->read();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
