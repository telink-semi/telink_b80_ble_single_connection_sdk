# V3.4.1.0 (Public release)

### Dependency Updates
   * telink_b85m_driver_sdk_V1.4.0
### Features
   * Work on B80 A0/A1 version
   * Support BLE4.2 ACL slave related function
   * Support 128/512K Flash and related OTA function
   * Support Low Power with suspend, deepsleep retention and deepsleep mode
   * Support 1M & 2M PHY

### BREAKING CHANGES
   * N/A

### CodeSize
   * Flash:
      - Disable deepsleep retention: 37.6k Byte
      - Enable deepsleep retention: 38.8k Byte
   * RAM:
      - Disable deepsleep retention: 11.8k Byte
      - Enable deepsleep retention: 13.3k Byte
   * > The values above are obtained by compiling 8208_sample with default configuration. 
### Dependency Updates
   * telink_b85m_driver_sdk_V1.4.0
### Features
   * 支持 B80 A0/A1 芯片
   * 支持 BLE4.2 ACL slave相关功能
   * 支持 128/512K Flash 及相应的OTA功能
   * 支持 Suspend、deepsleep retention和deepsleep 低功耗模式
   * 支持 1M & 2M PHY.

### BREAKING CHANGES
   * N/A

### CodeSize
   * Flash:
      - 关闭deepsleep retention: 37.6k Byte
      - 打开deepsleep retention: 38.8k Byte
   * RAM:
      - 关闭deepsleep retention: 11.8k Byte
      - 打开deepsleep retention: 13.3k Byte
   * >以上大小使用默认配置编译8208_sample得到