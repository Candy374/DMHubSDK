# 更新日志

## Version 0.2.0

_2017-05-18_

### 1. 更新说明

新增：
- 增加了对个推推送的支持。
- 增加了记录用户事件的重载方法。

修复：
- SDK 所需的 Android API 最低版本由 `API 15` 调整为 `API 9` 。
- 记录用户事件的自定义属性参数 `properties` 的类型由 `HashMap` 调整为 `Properties` 。

优化：
- Offline 场景下产生的事件会在 online 时进行补充记录。
- 对 SDK 性能进行了优化，降低了对 App 性能的影响。
- 对 SDK 开发文档进行了改进。

### 2. 开发须知
- AndroidManifest.xml 文件的配置有新增内容，请根据开发文档 [3.3 配置 AndroidManifest.xml](https://github.com/xsio/DMHubSDK/blob/master/dmhubsdk-android/dmhubsdk-0.2.0/GUIDE.md#33-配置-androidmanifestxml) 进行调整。


## Version 0.1.0

_2017-04-21_

最初版本。