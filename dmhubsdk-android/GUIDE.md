# Android SDK 开发指南



# 目录

- [1. 使用说明](#1-使用说明)

- [2. 开发准备](#2-开发准备)
  - [2.1 创建应用](#21-创建应用)
     - [2.1.1 进入应用设置页面](#211-进入应用设置页面)
     - [2.1.2 新建应用](#212-新建应用)
     - [2.1.3 更新权限设置](#213-更新权限设置)
  - [2.2 工程准备](#22-工程准备)

- [3. 导入 SDK](#3-导入-sdk)
  - [3.1 添加 jar 包](#31-添加-jar-包)
  - [3.2 配置 AndroidManifest.xml](#32-配置-androidmanifestxml)
     - [3.2.1 配置 SDK 所需权限](#321-配置-sdk-所需权限)
     - [3.2.2 配置 SDK 所需组件和参数](#322-配置-sdk-所需组件和参数)

- [4. 初始化](#4-初始化)

- [5. 创建客户和客户身份](#5-创建客户和客户身份)

- [6. 跟踪客户事件](#6-跟踪客户事件)
  - [6.1 跟踪进入视图事件](#61-跟踪进入视图事件)
  - [6.2 跟踪推送通知相关事件](#62-跟踪推送通知相关事件)
  - [6.3 跟踪客户自定义事件](#63-跟踪客户自定义事件)

- [7. 其他 API](#7-其他-api)

- [8. 混淆规则](#8-混淆规则)

- [9. 技术支持](#9-技术支持)



## 1. 使用说明

- 本文是 DMHub Android SDK 标准的开发指南文档，用以指导 SDK 的集成和使用，默认读者已经具备一定的 Android 开发能力。
- 本篇指南匹配的 DMHub Android SDK 版本为： `v0.3.1` 。
- DMHub Android SDK 0.3.1 要求  `Java >= 1.7`  &  `Android API >= 9` 。

## 2. 开发准备

### 2.1 创建应用

集成 DMHub SDK 之前，您首先需要到 DM Hub 平台创建应用。

#### 2.1.1 进入应用设置页面

点击 DM Hub 平台首页右上角的齿轮图标，选择 `开放与集成` 选项，进入应用设置页面。

![left | 0x0](../assets/guide01.png)

#### 2.1.2 新建应用

在应用设置页面点击右上角的 `+ 新建` 按钮，在弹出的创建应用弹出框中填写应用名称和描述后保存。

![left | 0x0](../assets/guide02.png)

#### 2.1.3 更新权限设置

创建应用成功之后，即可获得集成 SDK 所需的 appid 和 secret 信息。根据开发需求进行权限设置后，点击右下角的 `更新` 按钮（注：即使没有更改权限设置，也要进行更新），完成应用创建。

![left | 0x0](../assets/guide03.png)

### 2.2 工程准备

- 集成 `OkHttp3` 或 `Retrofit2` 。
- 集成 `极光推送` 或 `个推推送` 。

## 3. 导入 SDK

### 3.1 添加 jar 包

复制 libs 目录下的 [dmhubsdk-android-0.3.1.jar](libs/dmhubsdk-android-0.3.1.jar) 文件到工程主 module 的 libs 目录下，右键 jar 包，选择 `Add As Library...` ，将 jar 作为 Library 添加到主 module 中。

### 3.2 配置 AndroidManifest.xml

#### 3.2.1 配置 SDK 所需权限

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
```

如果需要获取客户设备的 IMEI 信息，还需要配置：

```xml
<uses-permission android:name="android.permission.READ_PHONE_STATE" />
```

添加该权限后，SDK 会默认获取客户设备的 IMEI 信息，并将其作为客户身份添加到客户信息中，可以在客户详情页查看。如果不需要获取客户设备的 IMEI 信息，请不要添加此权限。

#### 3.2.2 配置 SDK 所需组件和参数

在 AndroidManifest.xml 中的 `<application></application>` 标签内配置 SDK 所需组件和参数：

```xml
<!-- DMHubSDK 监听网络状态的 Receiver 组件 -->
<receiver android:name="com.convertlab.dmhubsdk.NetReceiver">
    <intent-filter>
        <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
    </intent-filter>
</receiver>

<!--
    如果您使用了极光推送，请配置该组件，SDK 会在该组件中记录通知推送相关事件；
    如果您没有使用极光推送，则不需要配置该组件。
-->
<receiver
    android:name="com.convertlab.dmhubsdk.JPushReceiver"
    android:enabled="true"
    android:exported="false">
    <intent-filter>
        <action android:name="cn.jpush.android.intent.REGISTRATION" />
        <action android:name="cn.jpush.android.intent.MESSAGE_RECEIVED" />
        <action android:name="cn.jpush.android.intent.NOTIFICATION_RECEIVED" />
        <action android:name="cn.jpush.android.intent.NOTIFICATION_OPENED" />
        <action android:name="cn.jpush.android.intent.CONNECTION" />
        <category android:name="您应用的包名" />
    </intent-filter>
</receiver>

<!-- DMHubSDK 相关参数 -->
<meta-data
    android:name="DMHubSDKAppId"
    android:value="在 DM Hub 平台获得的 appid" />
<meta-data
    android:name="DMHubSDKSecret"
    android:value="在 DM Hub 平台获得的 secret" />
```

如果您是在测试账号下创建的应用，则需要添加配置：

```xml
<meta-data
    android:name="DMHubServer"
    android:value="http://api.convertwork.cn" />
```

## 4. 初始化

在自定义的 `Application` 中的 `onCreate` 方法中调用初始化方法：

```java
public class DMHubApp extends Application {
    
    @Override
    public void onCreate() {
        super.onCreate();

        // 初始化 DMHubSDK，SDK 会在初始化时记录打开 App 事件
        DMHubSDK.sharedInstance().init(this);
    }
}
```

注：在整个应用程序全局，只需要进行一次初始化。

## 5. 创建客户和客户身份

为了跟踪客户事件，需要先创建客户和客户身份。

如果您使用了极光推送，需要配置 `JPushReceiver` 组件，正确配置后，SDK 内部会完成创建客户的操作。

如果您使用了个推推送，则需要调用下面的 API 进行创建客户：

- 接口定义

```java
public void fetchGeTuiClientId(@NonNull String clientId);
```

- 代码示例

```java
public class YourIntentService extends GTIntentService {

    @Override
    public void onReceiveClientId(Context context, String clientid) {
        DMHubSDK.sharedInstance().fetchGeTuiClientId(clientid);
    }
}
```

## 6. 跟踪客户事件

### 6.1 跟踪进入视图事件

- 接口定义

```java
/**
 * @param viewName 视图的名称，客户时间轴上的显示为：'进入手机视图 ${viewName}'
 */
public void trackOpenView(@NonNull String viewName);
```

- 代码示例

```java
public class YourActivity extends Activity {
    
    @Override
    protected void onResume() {
        super.onResume();
        
        DMHubSDK.sharedInstance().trackOpenView("<viewName>");
    }
}
```

### 6.2 跟踪推送通知相关事件

如果您使用了极光推送，需要配置 `JPushReceiver` 组件，正确配置后，SDK 内部会完成推送通知相关事件的记录。

如果您使用了个推推送，则需要调用下面的 API 进行记录：

- 接口定义

```java
/**
 * @param payload msg 中的 payload
 *
 * @return 如果传入的 payload 对应的推送来自 DM Hub 平台，返回 true；否则，返回 false
 */
public boolean fetchGeTuiMessage(@NonNull String payload);
```

- 代码示例

```java
public class YourIntentService extends GTIntentService {

    @Override
    public void onReceiveMessageData(Context context, GTTransmitMessage msg) {
        byte[] payload = msg.getPayload();
        if (payload != null) {
            boolean fromDMHub = DMHubSDK.sharedInstance().fetchGeTuiMessage(new String(payload));
        }
    }
}
```

### 6.3 跟踪客户自定义事件

注：该接口调用之前需要先根据业务需求在 DM Hub 后台新建自定义事件，在新建自定义事件时，还可以根据需要添加自定义属性。

- 接口定义

```java
/**
 * @param eventId    与 DM Hub 中新建的自定义事件对应的事件 Id
 * @param targetName 对于自定义事件，客户时间轴上只会显示 targetName，相当于事件标题
 * @param targetId   客户触发该事件对应的目标(如按钮)的 Id
 * @param properties 事件的自定义属性，必须以在 DM Hub 中新建自定义事件时添加的自定义属性作为 key
 */
public void track(@NonNull String eventId, @NonNull String targetName, String targetId, Properties properties);
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
            DMHubSDK.sharedInstance().track(
                "<eventId>",
                "<targetName，如：'首次打开 Android App'>",
                "<targetId，客户触发首次打开 App 事件对应的目标为 App，可以传入应用包名作为 targetId>",
                properties
            );
        }
    }
}
```

## 7. 其他 API

如果您使用了极光推送，可以通过下面的接口判断接收到的 JPush 推送是否来自 DM Hub 平台：

- 接口定义

```java
/**
 * @param intent 自定义的 JPush 广播接收器收到的 intent
 *
 * @return 如果传入的 intent 对应的推送来自 DM Hub 平台，返回 true；否则，返回 false
 */
public boolean isFromDMHubJPush(Intent intent);
```

- 代码示例

```java
public class YourReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        boolean fromDMHub = DMHubSDK.sharedInstance().isFromDMHubJPush(intent);
    }
}
```

## 8. 混淆规则

在工程的混淆规则文件中添加如下规则：

```prolog
# DMHubSDK
-dontwarn com.convertlab.dmhubsdk.**
-keep class com.convertlab.dmhubsdk.** { *; }
```

## 9. 技术支持

- 在线客服：在 DM Hub 平台右下角进行客服咨询
- 电子邮件：<support@convertlab.com>
