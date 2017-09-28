# 更新日志

## Version 1.1.0

_2017-09-28_

SDK 不再创建客户，交由 Server 端完成。


## Version 0.3.1

_2017-09-01_

性能优化。


## Version 0.3.0

_2017-07-17_

新增：
- 增加了判断推送通知是否来自 DM Hub 平台的接口。
- 增加了用于处理极光推送通知相关事件的 `JPushReceiver` 组件。

优化：
- 采用的推送平台无需再显式配置。
- 客户创建无需显式调用 API，交由 SDK 完成。
- 打开 App 事件的记录无需显式调用 API，交由 SDK 完成。
- 对于极光推送，注册 JPushReceiver 组件后，推送通知相关事件的记录完全交由 SDK 完成。

废弃：
- 废弃了创建客户的相关 API。
- 废弃了记录 `打开手机应用` 预置事件的相关 API。
- 废弃了 `退出手机应用` 预置事件及记录该事件的相关 API。
- 废弃了 `退出手机视图` 预置事件及记录该事件的相关 API。


## Version 0.2.1

_2017-06-01_

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


## Version 0.2.0

_2017-05-18_

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


## Version 0.1.0

_2017-04-21_

最初版本。
