// Created by Dong Zhong on 2021/09/13.

#import "ViewController.h"

#import <ReZero/ReZero.h>

@interface ViewController ()

@property (unsafe_unretained, nonatomic) IBOutlet UILabel *label;
@property (strong, nonatomic) IBOutlet ReZeroView *rezeroView;

@end

@implementation ViewController

- (void)viewDidLoad {
  [super viewDidLoad];
  // Do any additional setup after loading the view.
  self.label.text = [ReZeroView getVersion];
  [self.label sizeToFit];

  self.rezeroView = [ReZeroView new];
  [self.view addSubview:self.rezeroView];
}


@end
