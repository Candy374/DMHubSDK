//
//  DMHubSDK.h
//  DMHubSDK
//
//  Created by weichuancheng on 2018/4/13.
//  Copyright © 2018年 convertlab. All rights reserved.
//

#import <Foundation/Foundation.h>



/**
 DM Hub 客户身份
 */
@interface DMHubIdentity : NSObject

@property (nonatomic, readonly) NSString *type;
@property (nonatomic, readonly) NSString *value;

@end



@interface DMHubSDK : NSObject

#pragma mark - Start

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


#pragma mark - Identity

/**
 设置客户身份，用于绑定事件
 如果重复设置，将会使用新的客户身份进行事件绑定
 */
+ (void)setIdentityWithType:(NSString *)identityType
                      value:(NSString *)identityValue;

/**
 获取当前设置的客户身份

 @return 如果当前还未设置过有效的客户身份，返回 nil
 */
+ (DMHubIdentity *)currentIdentity;

/**
 清除当前设置的客户身份

 @return 当前设置的客户身份，如果当前还未设置过有效的客户身份，返回 nil
 */
+ (DMHubIdentity *)clearIdentity;


#pragma mark - Tracking

/**
 跟踪客户自定义事件

 @param eventId 在 DM Hub 中新建的自定义事件的事件 Id
 @param properties 事件的自定义属性，必须以在 DM Hub 中新建自定义事件时添加的自定义属性作为 key
 */
+ (void)trackWithEventId:(NSString *)eventId
              properties:(NSDictionary *)properties;

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


#pragma mark - About Push

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

/**
 跟踪收到 JPush 自定义消息事件

 @param notification JPush 收到自定义消息的回调方法中传入的 notification
 */
+ (void)trackReceiveJPushMessage:(NSNotification *_Nonnull)notification;

/**
 跟踪收到 GeTui 透传消息事件

 @param payloadData GeTui 收到透传消息的回调方法中传入的 payloadData
 @param offLine GeTui 收到透传消息的回调方法中传入的 offLine
 */
+ (void)trackReceiveGeTuiPayloadData:(NSData *_Nonnull)payloadData offLine:(BOOL)offLine;


#pragma mark - Configuration

/**
 是否仅在 WIFI 环境下上传数据，默认值：NO
 */
+ (BOOL)uploadOnlyWifi;

/**
 设置是否仅在 WIFI 环境下上传数据
 */
+ (void)setUploadOnlyWifi:(BOOL)uploadOnlyWifi;

/**
 是否允许 App 进入后台后上传数据，默认值：YES
 */
+ (BOOL)flushOnBackground;

/**
 设置是否允许 App 进入后台后上传数据
 */
+ (void)setFlushOnBackground:(BOOL)flushOnBackground;

/**
 是否自动跟踪进入、离开视图事件，默认值：NO
 */
+ (BOOL)autoTrackViewEvent;

/**
 设置是否自动跟踪进入、离开视图事件
 */
+ (void)setAutoTrackViewEvent:(BOOL)autoTrackViewEvent;

/**
 批量上传事件的时间间隔（单位：秒），默认值：30
 */
+ (NSUInteger)flushInterval;

/**
 设置批量上传事件的时间间隔（单位：秒）
 */
+ (void)setFlushInterval:(NSUInteger)flushInterval;

/**
 未上传事件队列中的事件数量限制，达到此限制时，即使未到批量上传事件的时间间隔（flushInterval），也会进行事件上传，默认值：40
 */
+ (NSUInteger)bulkUploadLimit;

/**
 设置未上传事件队列中的事件数量限制
 */
+ (void)setBulkUploadLimit:(NSUInteger)bulkUploadLimit;


#pragma mark - Logger

/**
 调试日志开关，Warning 和 Error 级别的日志不受此开关控制，正常情况下，不应该有 Warning 和 Error 级别的日志输出
 */
+ (void)enableDebugLog:(BOOL)enable;

/**
 调试日志是否打开，默认关闭
 */
+ (BOOL)debugLogEnabled;

@end
