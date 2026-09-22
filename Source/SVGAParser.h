//
//  SVGAParser.h
//  SVGAPlayer
//
//  Created by 崔明辉 on 16/6/17.
//  Copyright © 2016年 UED Center. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SVGAVideoEntity;

/**
 缓存 key 过滤 Block，与 SDWebImage 的 cacheKeyFilter 类似。

 在计算磁盘缓存 key 之前调用，可用于剔除 URL 中 sign、t 等动态变化的鉴权参数，
 避免同一资源因签名变化而反复下载。返回的字符串会再做一次 MD5 作为最终缓存 key；
 返回 nil 或空字符串时回退为 URL.absoluteString。
 */
typedef NSString * _Nullable (^SVGAParserCacheKeyFilterBlock)(NSURL * _Nonnull URL);

@interface SVGAParser : NSObject

@property (nonatomic, assign) BOOL enabledMemoryCache;

/**
 实例级缓存 key 过滤器，优先级高于 sharedCacheKeyFilter。
 */
@property (nonatomic, copy, nullable) SVGAParserCacheKeyFilterBlock cacheKeyFilter;

/**
 全局缓存 key 过滤器，对所有 SVGAParser 实例生效（含 SVGAImageView 内部持有的 sharedParser）。
 */
+ (void)setSharedCacheKeyFilter:(nullable SVGAParserCacheKeyFilterBlock)cacheKeyFilter;
+ (nullable SVGAParserCacheKeyFilterBlock)sharedCacheKeyFilter;

- (void)parseWithURL:(nonnull NSURL *)URL
     completionBlock:(void ( ^ _Nonnull )(SVGAVideoEntity * _Nullable videoItem))completionBlock
        failureBlock:(void ( ^ _Nullable)(NSError * _Nullable error))failureBlock;

- (void)parseWithURLRequest:(nonnull NSURLRequest *)URLRequest
            completionBlock:(void ( ^ _Nonnull )(SVGAVideoEntity * _Nullable videoItem))completionBlock
               failureBlock:(void ( ^ _Nullable)(NSError * _Nullable error))failureBlock;

- (void)parseWithData:(nonnull NSData *)data
             cacheKey:(nonnull NSString *)cacheKey
      completionBlock:(void ( ^ _Nullable)(SVGAVideoEntity * _Nonnull videoItem))completionBlock
         failureBlock:(void ( ^ _Nullable)(NSError * _Nonnull error))failureBlock;

- (void)parseWithNamed:(nonnull NSString *)named
              inBundle:(nullable NSBundle *)inBundle
       completionBlock:(void ( ^ _Nullable)(SVGAVideoEntity * _Nonnull videoItem))completionBlock
          failureBlock:(void ( ^ _Nullable)(NSError * _Nonnull error))failureBlock;

- (NSString * _Nullable)MD5String:(nonnull NSString * )str;

/** 下载SVGAData
 *
 */
- (void)downloadSVGADataWithURLString:(nonnull NSString *)URLString;
- (void)clearLocalSVGADataCacheWithURLString:(nonnull NSString *)URLString;

@end
