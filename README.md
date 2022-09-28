# V3.4.1.1 (Public release)

### Dependency Updates
   * telink_b85m_driver_sdk_V1.5.0
### Features
   * Support passive scanning in slave connection
   * Support passive scanning in advertising
   * Add APIs of saving RAM, but these APIs increase power consumption when called
   * Fix the issue that the pointer to packet is null when callback of BLT_EV_FLAG_CONNECT is triggered
   * Adapt Puya Flash
   * Add version information at the end of bin file.

### BREAKING CHANGES
   * N/A

### CodeSize
   * Flash:
      - Disable deepsleep retention: 39.4k Byte
      - Enable deepsleep retention: 40.3k Byte
   * RAM:
      - Disable deepsleep retention: 12.4k Byte
      - Enable deepsleep retention: 13.6k Byte
   * The values above are obtained by compiling 8208_ble_sample with default configuration. 

   * Flash:
      - Disable deepsleep retention: 39.3k Byte
      - Enable deepsleep retention: 39.7k Byte
   * RAM:
      - Disable deepsleep retention: 10.4k Byte
      - Enable deepsleep retention: 11.2k Byte
   * The values above are obtained by compiling 8208_ble_sample with calling APIs of saving RAM
### Dependency Updates
   * telink_b85m_driver_sdk_V1.5.0
### Features
   * 支持在连接中被动扫描
   * 支持在广播中被动扫描
   * 增加api来节省RAM，在调用时会增加平均功耗
   * 修复了触发BLT_EV_FLAG_CONNECT事件回调时指向数据包的指针为空的问题
   * 适配Puya Flash
   * bin文件末尾增加版本信息

### BREAKING CHANGES
   * N/A

### CodeSize
   * Flash:
      - 关闭deepsleep retention: 39.4k Byte
      - 打开deepsleep retention: 40.3k Byte
   * RAM:
      - 关闭deepsleep retention: 12.4k Byte
      - 打开deepsleep retention: 13.6k Byte
   * 以上大小使用默认配置编译8208_ble_sample得到

   * Flash:
      - 关闭deepsleep retention: 39.3k Byte
      - 打开deepsleep retention: 39.7k Byte
   * RAM:
      - 关闭deepsleep retention: 10.4k Byte
      - 打开deepsleep retention: 11.2k Byte
   * 以上大小时是调用节省ram的API后得到