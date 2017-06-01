# 更新日志

## Version 0.2.1

_2017-06-01_

### 1. 更新说明

新增：
- 增加了采集客户设备 IMEI 信息的功能。

修复：
- 修复了同时使用极光推送和个推推送时，有极小概率出现的创建出多个客户的问题。
- 修复了多次调用创建客户的方法可能创建出额外客户身份的问题。
- 修复了有极小概率出现的首次打开 App 的事件无法触发自动流程的问题。

优化：
- SDK 开发文档中对创建客户的方法进行了更详细的说明。

废弃：
- 废弃了 `DMHubCustomer` 和 `DMHubCustomerIdentity` 两个实体类。
- 废弃了 `customerAndIdentities(DMHubCustomer customer, ArrayList<DMHubCustomerIdentity> identities)` 方法。
- 带有 5 个参数的 `createUnknownCustomerWithJPushIdentity` 和 `createUnknownCustomerWithGeTuiIdentity` 两个创建客户的方法分别修改为 `createCustomerWithJPushIdentity` 和 `createCustomerWithGeTuiIdentity` 。

### 2. 开发须知

- 增加了采集客户设备 IMEI 信息的功能，请根据开发文档 [3.3.1 配置是否获取 IMEI 信息](https://github.com/xsio/DMHubSDK/blob/master/dmhubsdk-android/GUIDE.md#331-配置是否获取-imei-信息) 进行配置。
- SDK 开发文档中对创建客户的方法进行了更详细的说明，为了避免使用过程中出现问题，请前往开发文档 [5. 创建初始客户和客户身份](https://github.com/xsio/DMHubSDK/blob/master/dmhubsdk-android/GUIDE.md#5-创建初始客户和客户身份) 阅读详细说明。
- 如果曾在开发过程中使用了新版本 SDK 废弃的内容，请根据实际需求进行修改。


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

- AndroidManifest.xml 文件的配置有新增内容，请根据开发文档 [3.3 配置 AndroidManifest.xml](https://github.com/xsio/DMHubSDK/blob/master/dmhubsdk-android/GUIDE.md#33-配置-androidmanifestxml) 进行调整。


## Version 0.1.0

_2017-04-21_

最初版本。
