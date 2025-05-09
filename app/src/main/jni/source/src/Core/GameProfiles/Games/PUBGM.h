#pragma once

#include "../GameProfile.h"

// PUBGM
// UE 4.18

class PUBGMProfile : public IGameProfile
{
public:
    PUBGMProfile() = default;

    virtual bool ArchSupprted() const override
    {
        auto e_machine = GetBaseInfo().ehdr.e_machine;
        // arm & arm64
        return e_machine == EM_AARCH64 || e_machine == EM_ARM;
    }

    std::string GetAppName() const override
    {
        return "PUBG";
    }

    std::vector<std::string> GetAppIDs() const override
    {
        return {
            "com.pubg.imobile",
        };
    }

    bool IsUsingFNamePool() const override
    {
        return false;
    }

    uintptr_t GetGUObjectArrayPtr() const override {
    auto e_machine = GetBaseInfo().ehdr.e_machine;
    if (e_machine == EM_ARM) {
        return GetBaseInfo().map.startAddress + 0x8dfff58; // 32-bit offset
    } else if (e_machine == EM_AARCH64) {
        return GetBaseInfo().map.startAddress + 0xcad3dc0; // 64-bit offset
    }
    return 0;
}

uintptr_t GetNamesPtr() const override {
    auto e_machine = GetBaseInfo().ehdr.e_machine;
    if (e_machine == EM_ARM) {
        return PMemory::vm_rpm_ptr<uintptr_t>(PMemory::vm_rpm_ptr<uintptr_t>(GetBaseInfo().map.startAddress + 0x8C3A734) + 0x88); // 32-bit offset
    } else if (e_machine == EM_AARCH64) {
        return PMemory::vm_rpm_ptr<uintptr_t>(PMemory::vm_rpm_ptr<uintptr_t>(GetBaseInfo().map.startAddress + 0xc646620) + 0x110); // 64-bit offset
    }
    return 0;
}

    UE_Offsets *GetOffsets() const override
    {
        // ===============  64bit offsets  =============== //
        struct
        {
            uint16 Stride = 0;          // not needed in versions older than UE4.23
            uint16 FNamePoolBlocks = 0; // not needed in versions older than UE4.23
            uint16 FNameMaxSize = 0xff;
            struct
            {
                uint16 Number = 4;
            } FName;
            struct
            {
                uint16 Name = 0xC;
            } FNameEntry;
            struct
            { // not needed in versions older than UE4.23
                uint16 Info = 0;
                uint16 WideBit = 0;
                uint16 LenBit = 0;
                uint16 HeaderSize = 0;
            } FNameEntry23;
            struct
            {
                uint16 ObjObjects = 0x10;
            } FUObjectArray;
            struct
            {
                uint16 NumElements = 0x38;
            } TUObjectArray;
            struct
            {
                uint16 Size = 0x18;
            } FUObjectItem;
            struct
            {
                uint16 ObjectFlags = 0x8;
                uint16 InternalIndex = 0xC;
                uint16 ClassPrivate = 0x10;
                uint16 NamePrivate = 0x18;
                uint16 OuterPrivate = 0x20;
            } UObject;
            struct
            {
                uint16 Next = 0x28; // sizeof(UObject)
            } UField;
            struct
            {
                uint16 SuperStruct = 0x30; // sizeof(UField)
                uint16 Children = 0x38;    // UField*
                uint16 ChildProperties = 0;  // not needed in versions older than UE4.25
                uint16 PropertiesSize = 0x40;
            } UStruct;
            struct
            {
                uint16 Names = 0x40; // usually at sizeof(UField) + sizeof(FString)
            } UEnum;
            struct
            {
                uint16 EFunctionFlags = 0x88; // sizeof(UStruct)
                uint16 NumParams = EFunctionFlags + 0x4;
                uint16 ParamSize = NumParams + 0x2;
                uint16 Func = EFunctionFlags + 0x28; // ue3-ue4, always +0x28 from flags location.
            } UFunction;
            struct
            { // not needed in versions older than UE4.25
                uint16 ClassPrivate = 0;
                uint16 Next = 0;
                uint16 NamePrivate = 0;
                uint16 FlagsPrivate = 0;
            } FField;
            struct
            { // not needed in versions older than UE4.25
                uint16 ArrayDim = 0;
                uint16 ElementSize = 0;
                uint16 PropertyFlags = 0;
                uint16 Offset_Internal = 0;
                uint16 Size = 0;
            } FProperty;
            struct
            {
                uint16 ArrayDim = 0x30; // sizeof(UField)
                uint16 ElementSize = 0x34;
                uint16 PropertyFlags = 0x38;
                uint16 Offset_Internal = 0x44;
                uint16 Size = 0x70; // sizeof(UProperty)
            } UProperty;
        } static profile64;
        static_assert(sizeof(profile64) == sizeof(UE_Offsets));

        // ===============  32bit offsets  =============== //
        struct
        {
            uint16 Stride = 0;          // not needed in versions older than UE4.23
            uint16 FNamePoolBlocks = 0; // not needed in versions older than UE4.23
            uint16 FNameMaxSize = 0xff;
            struct
            {
                uint16 Number = 4;
            } FName;
            struct
            {
                uint16 Name = 0x8;
            } FNameEntry;
            struct
            { // not needed in versions older than UE4.23
                uint16 Info = 0;
                uint16 WideBit = 0;
                uint16 LenBit = 0;
                uint16 HeaderSize = 0;
            } FNameEntry23;
            struct
            {
                uint16 ObjObjects = 0x10;
            } FUObjectArray;
            struct
            {
                uint16 NumElements = 0x8;
            } TUObjectArray;
            struct
            {
                uint16 Size = 0x10;
            } FUObjectItem;
            struct
            {
                uint16 ObjectFlags = 0x4;
                uint16 InternalIndex = 0x8;
                uint16 ClassPrivate = 0xC;
                uint16 NamePrivate = 0x10;
                uint16 OuterPrivate = 0x18;
            } UObject;
            struct
            {
                uint16 Next = 0x1C; // sizeof(UObject)
            } UField;
            struct
            {
                uint16 SuperStruct = 0x20; // sizeof(UField)
                uint16 Children = 0x24;    // UField*
                uint16 ChildProperties = 0;  // not needed in versions older than UE4.25
                uint16 PropertiesSize = 0x28;
            } UStruct;
            struct
            {
                uint16 Names = 0x2C; // usually at sizeof(UField) + sizeof(FString)
            } UEnum;
            struct
            {
                uint16 EFunctionFlags = 0x58; // sizeof(UStruct)
                uint16 NumParams = EFunctionFlags + 0x4;
                uint16 ParamSize = NumParams + 0x2;
                uint16 Func = EFunctionFlags + 0x1C; // +0x1C (32bit) from flags location.
            } UFunction;
            struct
            { // not needed in versions older than UE4.25
                uint16 ClassPrivate = 0;
                uint16 Next = 0;
                uint16 NamePrivate = 0;
                uint16 FlagsPrivate = 0;
            } FField;
            struct
            { // not needed in versions older than UE4.25
                uint16 ArrayDim = 0;
                uint16 ElementSize = 0;
                uint16 PropertyFlags = 0;
                uint16 Offset_Internal = 0;
                uint16 Size = 0;
            } FProperty;
            struct
            {
                uint16 ArrayDim = 0x20; // sizeof(UField)
                uint16 ElementSize = 0x24;
                uint16 PropertyFlags = 0x28;
                uint16 Offset_Internal = 0x34;
                uint16 Size = 0x50; // sizeof(UProperty)
            } UProperty;
        } static profile32;
        static_assert(sizeof(profile32) == sizeof(UE_Offsets));

#ifdef __LP64__
        return (UE_Offsets *)&profile64;
#else
        return (UE_Offsets *)&profile32;
#endif
    }
};
