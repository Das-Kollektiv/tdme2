#pragma once

/**
 * Apple specific: Get clipboard content
 * @param buf buffer to fill with clipboard content
 * @param size buffer size
 */
extern "C" void appleGetClipboardContent(char* buf, int size);

/**
 * Apple specific: Set clipboard content
 * @param content c string content string
 */
extern "C" void appleSetClipboardContent(const char* content);
