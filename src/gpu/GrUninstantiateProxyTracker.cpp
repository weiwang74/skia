/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "GrUninstantiateProxyTracker.h"

#include "GrSurfaceProxy.h"
#include "GrSurfaceProxyPriv.h"

void GrUninstantiateProxyTracker::addProxy(GrSurfaceProxy* proxy) {
#ifdef SK_DEBUG
    using LazyType = GrSurfaceProxy::LazyInstantiationType;
    SkASSERT(LazyType::kUninstantiate == proxy->priv().lazyInstantiationType());
    for (int i = 0; i < fProxies.count(); ++i) {
        SkASSERT(proxy != fProxies[i]);
    }
#endif
    fProxies.push_back(proxy);
}

void GrUninstantiateProxyTracker::uninstantiateAllProxies() {
    for (int i = 0; i < fProxies.count(); ++i) {
        GrSurfaceProxy* proxy = fProxies[i];
        SkASSERT(proxy->priv().isSafeToUninstantiate());
        proxy->deInstantiate();
    }
}
