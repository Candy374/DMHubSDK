//
//  DMHubSDK.h
//  DMHubSDK
//
//  Created by 魏川程 on 2017/5/4.
//  Copyright © 2017年 Convertlab. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NSDictionary<NSString *, NSString *> * Properties;

@interface DMHubSDK : NSObject



/**
 启动 SDK

 @param appId 在 DM Hub 平台创建应用时获得的 appid
 */
+ (void)startWithAppId:(NSString *_Nonnull)appId;

/**
 启动 SDK，并设置运行环境

 @param appId 在 DM Hub 平台创建应用时获得的 appid
 @param prod 是否在生产环境上运行，如果传入 NO，则在验证环境运行
 */
+ (void)startWithAppId:(NSString *_Nonnull)appId
                inProd:(BOOL)prod;

/**
 设置客户身份，用于绑定事件。如果重复设置，将会使用新的客户身份进行事件绑定

 @param type 身份类型
 @param value 身份标识
 */
+ (void)setIdentityWithType:(NSString *_Nonnull)type
                      value:(NSString *_Nonnull)value;



/**
 跟踪自定义客户事件

 @param eventId 与 DM Hub 中新建的自定义事件对应的事件 Id
 @param properties 事件的自定义属性，必须以在 DM Hub 中新建自定义事件时添加的自定义属性作为 key
 */
+ (void)trackWithEventId:(NSString *_Nonnull)eventId
              properties:(Properties _Nullable)properties;

/**
 跟踪进入视图事件

 @param viewName 视图的名称
 */
+ (void)trackOpenView:(NSString *_Nonnull)viewName;

/**
 跟踪离开视图事件

 @param viewName 视图的名称
 */
+ (void)trackExitView:(NSString *_Nonnull)viewName;



/**
 跟踪收到 JPush 通知事件

 @param userInfo JPush 通知中的 userInfo
 @param jPushAppKey JPush 的 AppKey
 @return 如果传入的 userInfo 对应的 JPush 通知来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
+ (BOOL)trackReceiveJPushNoti:(NSDictionary *_Nonnull)userInfo
                  jPushAppKey:(NSString *_Nonnull)jPushAppKey;

/**
 跟踪点击 JPush 通知事件

 @param userInfo JPush 通知中的 userInfo
 @param jPushAppKey JPush 的 AppKey
 @return 如果传入的 userInfo 对应的 JPush 通知来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
+ (BOOL)trackClickJPushNoti:(NSDictionary *_Nonnull)userInfo
                jPushAppKey:(NSString *_Nonnull)jPushAppKey;

/**
 跟踪收到 JPush 自定义消息事件

 @param notification JPush 收到自定义消息的回调方法中传入的 notification
 @param jPushAppKey JPush 的 AppKey
 @return 如果传入的 notification 对应的 JPush 自定义消息来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
+ (BOOL)trackReceiveJPushMessage:(NSNotification *_Nonnull)notification
                     jPushAppKey:(NSString *_Nonnull)jPushAppKey;



/**
 跟踪收到 GeTui 通知事件

 @param userInfo GeTui 通知中的 userInfo
 @param geTuiAppKey GeTui 的 AppKey
 @return 如果传入的 userInfo 对应的 GeTui 通知来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
+ (BOOL)trackReceiveGeTuiNoti:(NSDictionary *_Nonnull)userInfo
                  geTuiAppKey:(NSString *_Nonnull)geTuiAppKey;

/**
 跟踪点击 GeTui 通知事件

 @param userInfo GeTui 通知中的 userInfo
 @param geTuiAppKey GeTui 的 AppKey
 @return 如果传入的 userInfo 对应的 GeTui 通知来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
+ (BOOL)trackClickGeTuiNoti:(NSDictionary *_Nonnull)userInfo
                geTuiAppKey:(NSString *_Nonnull)geTuiAppKey;

/**
 跟踪收到 GeTui 透传消息事件

 @param payloadData GeTui 收到透传消息的回调方法中传入的 payloadData
 @param offLine GeTui 收到透传消息的回调方法中传入的 offLine
 @param geTuiAppKey GeTui 的 AppKey
 @return 如果传入的 payloadData 对应的 GeTui 透传消息来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
+ (BOOL)trackReceiveGeTuiPayloadData:(NSData *_Nonnull)payloadData
                             offLine:(BOOL)offLine
                         geTuiAppKey:(NSString *_Nonnull)geTuiAppKey;

@end
