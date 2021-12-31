# V3.4.0.0-Alpha (Function release)

### Dependency Updates
   * telink_b85m_driver_sdk_V1.3.0
### Features
   * Work on IC A0 version.
   * Support BLE4.2 ACL slave related function.
   * Support 128/512K Flash and related OTA function.
   * Support Low Power with suspend & deepsleep mode.
### Known issues
   * A0 chip has a leakage issue in suspend/deepsleep with 32k RC,which lead to current added in long connection. Will be fixed in A1 version.(Jira:EAGL-2)
### Notes
   * Pass cellphone capability test.
   * Pass high-low temperature test.  

### BREAKING CHANGES
   * N/A

### CodeSize
   * Flash:35.7k Byte
   * RAM: 12k Byte

### Dependency Updates
   * telink_b85m_driver_sdk_V1.3.0
### Features
   * 支持 B80 A0芯片
   * 支持 BLE4.2 ACL slave相关功能
   * 支持 128/512K Flash 及相应的OTA功能
   * 支持 Suspend/deepsleep 低功耗模式
### Known issues
   * A0芯片Suspend/deepsleep 32kRC唤醒模式漏电，使长连接功耗增加，A1版本修复(Jira:EAGL-2)
### Notes
   * 通过手机兼容性测试
   * 通过高低温测试

### BREAKING CHANGES
   * N/A

### CodeSize
   * Flash：35.7k Byte
   * RAM: 12k Byte