LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_STATIC_LIBRARIES := sdl_net sdl_gfx sdl_ttf xml2 freetype intl
#LOCAL_SHARED_LIBRARIES := sdl sdl_mixer sdl_image png
#LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lz -lGLESv1_CM


LOCAL_MODULE := main

LOCAL_CFLAGS += -std=c++11 -DANDROID=1

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
Box2D/Common/b2Settings.cpp \
Box2D/Common/b2BlockAllocator.cpp \
Box2D/Common/b2Math.cpp \
Box2D/Common/b2StackAllocator.cpp \
Box2D/Dynamics/Contacts/b2CircleContact.cpp \
Box2D/Dynamics/Contacts/b2TOISolver.cpp \
Box2D/Dynamics/Contacts/b2Contact.cpp \
Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
Box2D/Dynamics/b2Island.cpp \
Box2D/Dynamics/b2Body.cpp \
Box2D/Dynamics/b2ContactManager.cpp \
Box2D/Dynamics/b2Fixture.cpp \
Box2D/Dynamics/b2WorldCallbacks.cpp \
Box2D/Dynamics/b2World.cpp \
Box2D/Dynamics/Joints/b2MouseJoint.cpp \
Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
Box2D/Dynamics/Joints/b2Joint.cpp \
Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
Box2D/Dynamics/Joints/b2GearJoint.cpp \
Box2D/Dynamics/Joints/b2WeldJoint.cpp \
Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
Box2D/Dynamics/Joints/b2LineJoint.cpp \
Box2D/Collision/b2Distance.cpp \
Box2D/Collision/Shapes/b2PolygonShape.cpp \
Box2D/Collision/Shapes/b2CircleShape.cpp \
Box2D/Collision/b2BroadPhase.cpp \
Box2D/Collision/b2TimeOfImpact.cpp \
Box2D/Collision/b2CollideCircle.cpp \
Box2D/Collision/b2DynamicTree.cpp \
Box2D/Collision/b2Collision.cpp \
Box2D/Collision/b2CollidePolygon.cpp \
main.cpp \
Button.cpp \
Texture.cpp \
Context.cpp \
Clouds.cpp \
BoxGame.cpp \
Drop.cpp \
Audio.cpp \
UserInterface.cpp \
Camera.cpp \
Globals.cpp \
Map.cpp \
Object.cpp \
Position.cpp \
simplexnoise.cpp \
Thing.cpp \
P1.cpp \
Window.cpp \
Timer.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
