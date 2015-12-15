//
//  AppDelegate.h
//  eMMaSampleApp-iOS
//
//  Created by Adrian on 14/12/15.
//  Copyright © 2015 eMMa. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "eMMa.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate, eMMaPushDelegate>

@property (strong, nonatomic) UIWindow *window;


@end

