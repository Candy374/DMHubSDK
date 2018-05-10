# iOS SDK 开发指南



# 目录

- [1. 使用说明](#1-使用说明)

- [2. 创建应用](#2-创建应用)
  - [2.1 进入应用设置页面](#21-进入应用设置页面)
  - [2.2 新建应用](#22-新建应用)

- [3. 导入 SDK](#3-导入-sdk)
  - [3.1 添加 SDK 文件](#31-添加-sdk-文件)
  - [3.2 引入头文件](#32-引入头文件)

- [4. 初始化](#4-初始化)

- [5. 客户身份](#5-客户身份)
  - [5.1 设置客户身份](#51-设置客户身份)
  - [5.2 当前客户身份](#52-当前客户身份)
  - [5.3 清除客户身份](#53-清除客户身份)

- [6. 跟踪客户事件](#6-跟踪客户事件)
  - [6.1 跟踪客户自定义事件](#61-跟踪客户自定义事件)
  - [6.2 跟踪进入、离开视图事件](#62-跟踪进入离开视图事件)
  - [6.3 跟踪通知推送相关事件](#63-跟踪通知推送相关事件)
     - [6.3.1 设置消息推送相关信息](#631-设置消息推送相关信息)
     - [6.3.2 跟踪 JPush 推送相关事件](#632-跟踪-jpush-推送相关事件)
     - [6.3.3 跟踪 GeTui 推送相关事件](#633-跟踪-getui-推送相关事件)



## 1. 使用说明

- 本文是 DMHub iOS SDK 标准的开发指南文档，用以指导 SDK 的集成和使用，默认读者已经具备一定的 iOS 开发能力。
- 本篇指南匹配的 DMHub iOS SDK 版本为： `v2.0.0` 。
- DMHub iOS SDK 2.0.0 要求  `iOS >= 7.0` 。

## 2. 创建应用

集成 DMHub SDK 之前，您首先需要到 DM Hub 平台创建应用。

### 2.1 进入应用设置页面

点击 DM Hub 平台首页右上角的齿轮图标，选择 `开放与集成` 选项，进入应用设置页面。

![left | 0x0](../assets/guide01.png)

### 2.2 新建应用

在应用设置页面点击右上角的 `+ 新建` 按钮，在弹出的创建应用弹出框中填写应用信息后保存。应用创建成功之后，即可获得集成 SDK 所需的 appid。

![left | 0x0](../assets/guide02.png)

## 3. 导入 SDK

### 3.1 添加 SDK 文件

将 [libs 目录](libs) 下的 DMHubSDK.framework 库拷贝到工程目录下，然后在 Xcode 中的 `TARGETS` ---> `General` ---> `Linked Frameworks and Libraries` 中点击 `+` 进行添加，或者直接将库文件拖入。

### 3.2 引入头文件

在需要使用 DMHubSDK 功能的文件中引入头文件：

```objectivec
#import <DMHubSDK/DMHubSDK.h>
```

## 4. 初始化

使用 SDK 记录事件之前需要先进行启动，在整个应用程序全局，只需要启动一次，SDK 提供了多个启动方法，请开发者根据实际需求选择。

- 接口定义

```objectivec
/**
 启动 DMHubSDK

 @param appId 在 DM Hub 平台创建应用时获得的 appid
 @param launchOptions Application 的启动参数
 */
+ (void)startWithAppId:(NSString *)appId
         launchOptions:(NSDictionary *)launchOptions;

/**
 启动 DMHubSDK

 @param appId 在 DM Hub 平台创建应用时获得的 appid
 @param endpoint 如果不是在标准生产环境运行 DMHubSDK，需要配置该参数，默认值：@"https://api.convertlab.com"
 @param launchOptions Application 的启动参数
 */
+ (void)startWithAppId:(NSString *)appId
              endpoint:(NSString *)endpoint
         launchOptions:(NSDictionary *)launchOptions;

/**
 启动 DMHubSDK

 @param appId 在 DM Hub 平台创建应用时获得的 appid
 @param endpoint 如果不是在标准生产环境运行 DMHubSDK，需要配置该参数，默认值：@"https://api.convertlab.com"
 @param autoTrackViewEvent 是否自动记录进入、离开视图事件，默认值：NO
 @param flushInterval 上传数据的时间间隔（单位：秒），默认值：30
 @param launchOptions Application 的启动参数
 */
+ (void)startWithAppId:(NSString *)appId
              endpoint:(NSString *)endpoint
    autoTrackViewEvent:(BOOL)autoTrackViewEvent
         flushInterval:(NSUInteger)flushInterval
         launchOptions:(NSDictionary *)launchOptions;
```

- 代码示例

在 `AppDelegate.m` 文件中的 `- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions` 方法中启动 DMHubSDK：

```objectivec
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // 启动 DMHubSDK
    [DMHubSDK startWithAppId:@"<在 DM Hub 平台获得的 appid>" launchOptions:launchOptions];

    return YES;
}
```

## 5. 客户身份

客户身份是 DM Hub 中客户的标识，App 端 SDK 采集到的客户事件以及客户相关信息需要通过客户身份与客户进行绑定。

### 5.1 设置客户身份

为了将客户事件以及客户相关信息与客户绑定，需要在 App 获取到客户身份信息时（如客户注册或登录），设置客户身份。

多次调用设置身份接口，新的身份将会覆盖旧的身份，此后产生的客户事件将与新身份对应的客户绑定。

客户在未设置客户身份期间产生的事件将会作为匿名事件进行记录，匿名事件会保存 30 天。

- 接口定义

```objectivec
/**
 设置客户身份，用于绑定事件
 如果重复设置，将会使用新的客户身份进行事件绑定
 */
+ (void)setIdentityWithType:(NSString *)identityType
                      value:(NSString *)identityValue;
```

### 5.2 当前客户身份

获取当前设置的客户身份。

- 接口定义

```objectivec
/**
 获取当前设置的客户身份

 @return 如果当前还未设置过有效的客户身份，返回 nil
 */
+ (DMHubIdentity *)currentIdentity;
```

### 5.3 清除客户身份

清除客户身份之后产生的客户事件将会作为匿名事件进行记录。

- 接口定义

```objectivec
/**
 清除当前设置的客户身份

 @return 当前设置的客户身份，如果当前还未设置过有效的客户身份，返回 nil
 */
+ (DMHubIdentity *)clearIdentity;
```

## 6. 跟踪客户事件

### 6.1 跟踪客户自定义事件

根据业务需求在 DM Hub 后台 [新建自定义事件](../EVENT_GUIDE.md) 后，可以调用该 API 对自定义客户事件进行跟踪。在新建自定义事件时，还可以根据需要添加自定义属性，并在调用 API 时作为参数传入。

- 接口定义

```objectivec
/**
 跟踪客户自定义事件

 @param eventId 在 DM Hub 中新建的自定义事件的事件 Id
 @param properties 事件的自定义属性，必须以在 DM Hub 中新建自定义事件时添加的自定义属性作为 key
 */
+ (void)trackWithEventId:(NSString *)eventId
              properties:(NSDictionary *)properties;
```

### 6.2 跟踪进入、离开视图事件

如果设置了自动跟踪进入、离开视图事件，则不需要在调用以下两个 API 进行跟踪。

- 接口定义

```objectivec
/**
 跟踪进入视图事件

 @param viewName 视图的名称，客户时间轴上的显示为：'进入手机视图 ${viewName}'
 */
+ (void)trackOpenView:(NSString *)viewName;

/**
 跟踪离开视图事件

 @param viewName 视图的名称，客户时间轴上的显示为：'进入手机视图 ${viewName}'
 */
+ (void)trackExitView:(NSString *)viewName;
```

- 代码示例

```objectivec
@implementation YourViewController

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    // 跟踪进入视图事件
    [DMHubSDK trackOpenView:@"<viewName>"];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    // 跟踪离开视图事件
    [DMHubSDK trackExitView:@"<viewName>"];
}

@end
```

### 6.3 跟踪通知推送相关事件

如果您使用了 DM Hub 平台提供的通知推送功能，则可以调用 SDK 提供的相关 API 对来自 DM Hub 平台的通知推送相关事件进行跟踪。

#### 6.3.1 设置消息推送相关信息

为了采集消息推送相关信息，跟踪来自 DM Hub 平台的通知推送相关事件，DMHubSDK 需要获取您在推送服务商注册应用时获得的 AppKey，以及推送服务商分配给设备的标识（极光的 registrationID、个推的 clientId）。

- 接口定义

```objectivec
/**
 设置消息推送的相关信息，以便通过 DM Hub 对客户进行 App 消息推送

 @param appKey 在推送服务商注册应用时获得的 AppKey
 @param provider 推送服务商，目前支持极光（@"jpush"）和个推（@"getui"）
 */
+ (void)setAppKey:(NSString *)appKey
      forProvider:(NSString *)provider;

/**
 设置消息推送的相关信息，以便通过 DM Hub 对客户进行 App 消息推送

 @param appKey 在推送服务商注册应用时获得的 AppKey
 @param pushId 推送服务商分配给设备的标识，极光的 registrationID 或个推的 clientId
 @param provider 推送服务商，目前支持极光（@"jpush"）和个推（@"getui"）
 */
+ (void)setAppKey:(NSString *)appKey
           pushId:(NSString *)pushId
      forProvider:(NSString *)provider;
```

#### 6.3.2 跟踪 JPush 推送相关事件

- 接口定义

```objectivec
/**
 跟踪收到 JPush 自定义消息事件

 @param notification JPush 收到自定义消息的回调方法中传入的 notification
 */
+ (void)trackReceiveJPushMessage:(NSNotification *_Nonnull)notification;
```

- 代码示例

```objectivec
// 收到 JPush 自定义消息的回调
- (void)didReceiveJPushMessage:(NSNotification *)notification {
    [DMHubSDK trackReceiveJPushMessage:notification];
}
```

#### 6.3.3 跟踪 GeTui 推送相关事件

- 接口定义

```objectivec
/**
 跟踪收到 GeTui 透传消息事件

 @param payloadData GeTui 收到透传消息的回调方法中传入的 payloadData
 @param offLine GeTui 收到透传消息的回调方法中传入的 offLine
 */
+ (void)trackReceiveGeTuiPayloadData:(NSData *_Nonnull)payloadData offLine:(BOOL)offLine;
```

- 代码示例

```objectivec
// 收到 GeTui 透传消息的回调
- (void)GeTuiSdkDidReceivePayloadData:(NSData *)payloadData andTaskId:(NSString *)taskId andMsgId:(NSString *)msgId andOffLine:(BOOL)offLine fromGtAppId:(NSString *)appId {
    [DMHubSDK trackReceiveGeTuiPayloadData:payloadData offLine:offLine];
}
```
