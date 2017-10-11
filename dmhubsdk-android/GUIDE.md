# Android SDK 开发指南



# 目录

- [1. 使用说明](#1-使用说明)

- [2. 创建应用](#2-创建应用)
  - [2.1 进入应用设置页面](#21-进入应用设置页面)
  - [2.2 新建应用](#22-新建应用)

- [3. 导入 SDK](#3-导入-sdk)
  - [3.1 添加 jar 包](#31-添加-jar-包)
  - [3.2 配置 AndroidManifest.xml](#32-配置-androidmanifestxml)

- [4. 初始化](#4-初始化)

- [5. 设置客户身份](#5-设置客户身份)

- [6. 跟踪客户事件](#6-跟踪客户事件)
  - [6.1 跟踪进入、离开视图事件](#61-跟踪进入离开视图事件)
  - [6.2 跟踪通知推送相关事件](#62-跟踪通知推送相关事件)
     - [6.2.1 跟踪 JPush 推送相关事件](#621-跟踪-jpush-推送相关事件)
     - [6.2.2 跟踪 GeTui 推送相关事件](#622-跟踪-getui-推送相关事件)
  - [6.3 跟踪自定义客户事件](#63-跟踪自定义客户事件)

- [7. 混淆规则](#7-混淆规则)

- [8. 技术支持](#8-技术支持)



## 1. 使用说明

- 本文是 DMHub Android SDK 标准的开发指南文档，用以指导 SDK 的集成和使用，默认读者已经具备一定的 Android 开发能力。
- 本篇指南匹配的 DMHub Android SDK 版本为： `v1.1.0` 。
- DMHub Android SDK 1.1.0 要求  `Java >= 1.7`  &  `Android API >= 9` 。

## 2. 创建应用

集成 DMHub SDK 之前，您首先需要到 DM Hub 平台创建应用。

### 2.1 进入应用设置页面

点击 DM Hub 平台首页右上角的齿轮图标，选择 `开放与集成` 选项，进入应用设置页面。

![left | 0x0](../assets/guide01.png)

### 2.2 新建应用

在应用设置页面点击右上角的 `+ 新建` 按钮，在弹出的创建应用弹出框中填写应用信息后保存。应用创建成功之后，即可获得集成 SDK 所需的 appid。

![left | 0x0](../assets/guide02.png)

## 3. 导入 SDK

### 3.1 添加 jar 包

复制 libs 目录下的 [dmhubsdk-android-1.1.0.jar](libs/dmhubsdk-android-1.1.0.jar) 文件到工程主 module 的 libs 目录下，右键 jar 包，选择 `Add As Library...` ，将 jar 作为 Library 添加到主 module 中。

### 3.2 配置 AndroidManifest.xml

- 配置 SDK 所需权限

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
```

- 配置 SDK 所需参数

在 AndroidManifest.xml 中的 `<application></application>` 标签内配置 SDK 所需参数：

```xml
<!-- DMHubSDK 所需参数 -->
<meta-data
    android:name="DMHubSDKAppId"
    android:value="在 DM Hub 平台获得的 appid" />
```

## 4. 初始化

使用 SDK 记录事件之前需要先进行初始化，在整个应用程序全局，只需要进行一次初始化，SDK 会在初始化时记录打开 App 事件。

- 接口定义

```java
/**
 * 在自定义的 Application 中初始化 DMHubSDK
 * 在整个应用程序全局，只需要进行一次初始化，SDK 会在初始化时记录打开 App 事件
 *
 * @param prod 是否在生产环境上运行，如果传入 false，则在验证环境运行
 */
public static void init(@NonNull Context context, boolean prod);
```

- 代码示例

在自定义的 `Application` 中的 `onCreate` 方法中进行初始化：

```java
public class YourApp extends Application {
    
    @Override
    public void onCreate() {
        super.onCreate();

        // 初始化 DMHubSDK
        DMHubSDK.init(this, true);
    }
}
```

## 5. 设置客户身份

为了将客户事件绑定到客户身上，需要在 App 获取到客户身份信息时，设置客户身份。匿名事件会保存 30 天。

- 接口定义

```java
/**
 * 设置客户身份，用于绑定事件
 * 如果重复设置，将会使用新的客户身份进行事件绑定
 */
public static void setIdentity(@NonNull String identityType, @NonNull String identityValue);
```

## 6. 跟踪客户事件

### 6.1 跟踪进入、离开视图事件

- 接口定义

```java
/**
 * 跟踪进入视图事件
 *
 * @param viewName 视图的名称，客户时间轴上的显示为：'进入手机视图 ${viewName}'
 */
public static void trackOpenView(@NonNull String viewName);

/**
 * 跟踪离开视图事件
 *
 * @param viewName 视图的名称，客户时间轴上的显示为：'离开手机视图 ${viewName}'
 */
public static void trackExitView(@NonNull String viewName);
```

- 代码示例

```java
public class YourActivity extends Activity {
    
    @Override
    protected void onResume() {
        super.onResume();
        
        DMHubSDK.trackOpenView("<viewName>");
    }

    @Override
    protected void onPause() {
        super.onPause();

        DMHubSDK.trackExitView("<viewName>");
    }
}
```

### 6.2 跟踪通知推送相关事件

如果您使用了 DM Hub 平台提供的通知推送功能，则可以调用 SDK 提供的相关 API 对来自 DM Hub 平台的通知推送相关事件进行跟踪。

#### 6.2.1 跟踪 JPush 推送相关事件

- 接口定义

```java
/**
 * @param jPushIntent 自定义 JPush 广播接收器收到的 intent
 * @return 如果传入的 jPushIntent 对应的推送来自 DM Hub 平台，返回 true；否则，返回 false
 */
public static boolean trackJPushNotiEvent(@NonNull Intent jPushIntent);
```

- 代码示例

```java
public class YourJPushReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        DMHubSDK.trackJPushNotiEvent(intent);
    }
}
```

#### 6.2.2 跟踪 GeTui 推送相关事件

- 接口定义

```java
/**
 * @param geTuiPayload 自定义 GTIntentService 收到的推送消息中的 payload
 * @return 如果传入的 geTuiPayload 对应的推送来自 DM Hub 平台，返回 true；否则，返回 false
 */
public static boolean trackGeTuiNotiEvent(@NonNull String geTuiPayload);
```

- 代码示例

```java
public class YourIntentService extends GTIntentService {

    @Override
    public void onReceiveMessageData(Context context, GTTransmitMessage msg) {
        byte[] payload = msg.getPayload();
        if (payload != null) {
            boolean fromDMHub = DMHubSDK.trackGeTuiNotiEvent(new String(payload));
        }
    }
}
```

### 6.3 跟踪自定义客户事件

根据业务需求在 DM Hub 后台新建自定义事件后，可以调用该 API 对自定义客户事件进行跟踪。在新建自定义事件时，还可以根据需要添加自定义属性，并在调用 API 时作为参数传入。

- 接口定义

```java
/**
 * 跟踪自定义客户事件
 *
 * @param eventId    与 DM Hub 中新建的自定义事件对应的事件 Id
 * @param properties 事件的自定义属性，必须以在 DM Hub 中新建自定义事件时添加的自定义属性作为 key
 */
public static void track(@NonNull String eventId, Properties properties);
```

- 代码示例

```java
public class FirstActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // 记录首次打开 App 事件的示例
        if (<首次打开 App>) {
            Properties properties = new Properties();
            properties.setProperty("<自定义属性>", "<首次打开 App 事件对应的自定义属性值>");
            DMHubSDK.track("<eventId>", properties);
        }
    }
}
```

## 7. 混淆规则

在工程的混淆规则文件中添加如下规则：

```prolog
# DMHubSDK
-dontwarn com.convertlab.dmhubsdk.**
-keep class com.convertlab.dmhubsdk.** { *; }
```

## 8. 技术支持

- 在线客服：点击 DM Hub 平台右侧的 `客服咨询` 按钮进行咨询
- 电子邮件：<support@convertlab.com>

