//
//  eMMaDefines.h
//  eMMa
//
//  Created by Jaume Cornadó Panadés on 11/11/14.
//  Copyright (c) 2014 moddity. All rights reserved.
//
#import <UIKit/UIKit.h>

#ifndef eMMa_eMMaDefines_h
#define eMMa_eMMaDefines_h

typedef void(^imageCompletionBlock)(UIImage *image);

/**
 StartView Options
 */
typedef NS_OPTIONS(NSUInteger, eMMaStartViewOptions) {
    eMMaStartViewManualCall = (1 << 0),
    eMMaStartViewOpenLinksInSafari = (1 << 1)
};

typedef NS_OPTIONS(NSUInteger, eMMaAdBallOptions) {
    eMMaAdBallNotInBackground = (1 << 0),
    eMMaAdBallManualCall = (1 << 1)
};

typedef NS_OPTIONS(NSUInteger, keMMaPromotionType) {
    keMMaPromotionStartView,
    keMMaPromotionAdBall,
    keMMaPromotionBanner,
    keMMaPromotionAdBallWebView,
    keMMaPromotionTextBanner,
    keMMaPromotionTabBar
};

typedef NS_OPTIONS(NSUInteger, eMMaPushSystemOptions) {
    eMMaPushSystemDisableAlert = (1 << 0)
};

typedef NS_OPTIONS(NSUInteger, eMMaPushType) {
    PushTypePressedOnShutdown = 0,
    PushTypePressedOnBackground = 1,
    PushTypeNotPressedOnShutdown = 2,
    PushTypeNotPressedOnBackground = 3,
    PushTypeOnActive = 4
};

typedef NS_OPTIONS(NSUInteger, eMMaCommunicationType) {
    CommunicationTypePush = 1,
    CommunicationTypeWebview = 2,
    CommunicationTypeTabbar = 3,
    CommunicationTypeAdball = 4,
    CommunicationTypeBanner = 5,
    CommunicationTypeTextBanner = 6,
    CommunicationTypeOffer = 7,
};

/** Block definition for recovering the pushtags */
typedef void(^eMMaPushTagBlock)(NSString* pushTag, NSString* pushTagID);

/** Block definition for recovering userInfo */
typedef void(^eMMaGetUserInfoBlock)(NSDictionary* userInfo);

/** Block definition for recovering userId */
typedef void(^eMMaGetUserIdBlock)(NSString* userId);

/** Block definition for recovering coupons */
typedef void(^eMMaGetCouponsBlock)(NSDictionary* couponsResponse);

/**
 This protocol defines the delegate methods of the push system
 */
@protocol eMMaPushDelegate <NSObject>

@optional
/**
 Sends the pushtag to the delegate when a push is received
 
 @param pushTag the push tag on the push message
 */
-(void)pushTag:(NSString*)pushTag;

/**
 Sends the message to the delegate when a push is received
 
 @param pushMessage the content of the push message
 */
-(void)pushMessage:(NSString*)pushMessage;
@end

/**
 *  This protocol defines the delegate methods of the StartView
 */
@protocol eMMaStartViewDelegate <NSObject>

@optional

/**
 *  Called when a user navigates through the StartView
 *
 *  @param url the url loaded in StartView
 */
-(void) openedURLFromStartView:(NSURL*) url;

@end


#endif
