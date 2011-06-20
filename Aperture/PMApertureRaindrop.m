//
//  PMApertureRaindrop.m
//  Aperture
//
//  Created by Parker Moore on 6/19/11.
//  Copyright 2011 Linebreak. All rights reserved.
//

#import "PMApertureRaindrop.h"


@implementation PMApertureRaindrop

- (NSString *)pasteboardNameForTriggeredRaindrop
{
    ApertureApplication *aperture = [SBApplication applicationWithBundleIdentifier:@"com.apple.Aperture"];
	NSArray *selectedPhotos = [aperture selection];
    
	if (selectedPhotos == nil || [selectedPhotos count] == 0) {
		return nil;
    }
    
    NSMutableArray *items = [NSMutableArray array];
	for (AperturePhoto *photo in selectedPhotos) {
		if ([photo isKindOfClass:NSClassFromString(@"AperturePhoto")]) { // Hack to keep compiler happy
			NSPasteboardItem *item = [[NSPasteboardItem alloc] init];
			[item setString:[[NSURL fileURLWithPath:[photo imagePath]] absoluteString] forType:(NSString *)kUTTypeFileURL];
			[items addObject:item];
			[item release];
		}
	}
    
    if ([items count] == 0) {
        return nil;
	}
    
    NSPasteboard *pasteboard = [NSPasteboard pasteboardWithUniqueName];
	[pasteboard writeObjects:items];
    return pasteboard.name;
}

@end
