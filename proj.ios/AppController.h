#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    RootViewController    *viewController;
}

@property (nonatomic, strong) UIWindow *window;
@end

