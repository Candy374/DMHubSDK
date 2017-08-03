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
 在 Info.plist 文件中配置的 DMHubSDKAppId
 */
@property (nonatomic, readonly, copy) NSString * _Nullable appId;

/**
 在 Info.plist 文件中配置的 DMHubSDKSecret
 */
@property (nonatomic, readonly, copy) NSString * _Nullable secret;



#pragma mark - 单例模式
+ (instancetype _Nonnull)shared;



#pragma mark - 创建客户和客户身份
/**
 添加客户的 JPush 身份信息

 @param jPushAppKey JPush 的 AppKey
 @param jPushId     JPush SDK 向 JPush Server 注册得到的注册 Id
 */
- (void)fetchJPushAppKey:(NSString *_Nonnull)jPushAppKey
                 jPushId:(NSString *_Nonnull)jPushId;

/**
 添加客户的 GeTui 身份信息

 @param geTuiAppKey GeTui 的 AppKey
 @param geTuiId     GeTui SDK 向 GeTui Server 注册得到的 clientId
 */
- (void)fetchGeTuiAppKey:(NSString *_Nonnull)geTuiAppKey
                 geTuiId:(NSString *_Nonnull)geTuiId;

/**
 添加客户的广告标识符（IDFA）信息
 
 如果不需要使用 IDFA，请不要调用此方法。调用此方法后，IDFA 将会添加为客户的一个身份
 
 @param advertisingIdentifier 广告标识符（IDFA）
 */
- (void)fetchIdfa:(NSString *_Nonnull)advertisingIdentifier;



#pragma mark - 跟踪客户事件
/**
 跟踪自定义客户事件
 
 @param eventId    与 DM Hub 中新建的自定义事件对应的事件 Id
 @param targetName 对于自定义事件，客户时间轴上只会显示 targetName，相当于事件标题
 @param targetId   客户触发该事件对应的目标(如按钮)的 Id
 @param properties 事件的自定义属性，必须以在 DM Hub 中新建自定义事件时添加的自定义属性作为 key
 */
- (void)trackWithEventId:(NSString *_Nonnull)eventId
              targetName:(NSString *_Nonnull)targetName
                targetId:(NSString *_Nullable)targetId
              properties:(Properties _Nullable)properties;

/**
 跟踪进入视图事件

 @param viewName 视图的名称，客户时间轴上的显示为：'进入手机视图 ${viewName}'
 */
- (void)trackOpenView:(NSString *_Nonnull)viewName;

/**
 跟踪收到推送通知事件

 @param userInfo 推送通知中的 userInfo
 @return 如果传入的 userInfo 对应的推送通知来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
- (BOOL)trackReceiveNotification:(NSDictionary *_Nonnull)userInfo;

/**
 跟踪点击推送通知事件

 @param userInfo 推送通知中的 userInfo
 @return 如果传入的 userInfo 对应的推送通知来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
- (BOOL)trackClickNotification:(NSDictionary *_Nonnull)userInfo;

/**
 跟踪收到 JPush 自定义消息事件

 @param notification JPush 收到自定义消息的回调方法中传入的 notification
 @return 如果传入的 notification 对应的 JPush 自定义消息来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
- (BOOL)trackReceiveJPushMessage:(NSNotification *_Nonnull)notification;

/**
 跟踪收到 GeTui 透传消息事件

 @param payloadData GeTui 收到透传消息的回调方法中传入的 payloadData
 @param offLine GeTui 收到透传消息的回调方法中传入的 offLine
 @return 如果传入的 payloadData 对应的 GeTui 透传消息来自 DM Hub 平台，返回 YES；否则，返回 NO
 */
- (BOOL)trackReceiveGeTuiPayloadData:(NSData *_Nonnull)payloadData
                             offLine:(BOOL)offLine;

@end
