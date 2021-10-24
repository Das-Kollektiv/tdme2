#include <string.h>
#include <Cocoa/Cocoa.h>

void appleGetClipboardContent(char* buf, int size) {
	// see: https://github.com/floooh/sokol/blob/master/sokol_app.h
	@autoreleasepool {
		NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
		if ([[pasteboard types] containsObject:NSPasteboardTypeString] == false) {
			return;
		}
		NSString* str = [pasteboard stringForType:NSPasteboardTypeString];
		if (str == NULL) {
			return;
		}
		strncpy(buf, [str UTF8String], size);
	}
}

void appleSetClipboardContent(const char* content) {
	// see: https://github.com/floooh/sokol/blob/master/sokol_app.h
	@autoreleasepool {
		NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
		[pasteboard declareTypes:@[NSPasteboardTypeString] owner:nil];
		[pasteboard setString:@(content) forType:NSPasteboardTypeString];
	}
}
