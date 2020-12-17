#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>

enum AppleEmbeddedNVMeControllerAction {
    kNVMECTL_sendNVMECommandAction = 2,
    kNVMECTL_isBFHModeAction = 3,
    kNVMECTL_performBFHAction = 4,
    kNVMECTL_getNandDescriptorAction = 5,
    kNVMECTL_setNVMeStateAction = 6,
    kNVMECTL_setPCIPortStateAction = 7,
    kNVMECTL_setBFHGPIOAction = 8,
};

typedef struct NVMeIdentifyControllerStruct {
    char unknown[0x1000];
} NVMeIdentifyControllerStruct; // Unimplemented

class NVMeUpdateLib {

	public:
		NVMeUpdateLib();
		~NVMeUpdateLib();
		void DumpIdentifyData();
		void FirmwareDownload(void* nandDescriptor, void* responseData);
		void FirmwareValidate(char* fileBuffer);
		void FirmwareVersionCheck(char* data, size_t size, uint32_t mspType);
		kern_return_t GetClogMismatch(bool *misMatchout);
		kern_return_t GetMSPType(uint32_t *mspTypeOut);
		kern_return_t GetNANDDescriptor(uint64_t* nandDescriptor);
		kern_return_t IdentifyController(NVMeIdentifyControllerStruct* identity);
		kern_return_t IsBFHMode(bool* bfhModeOut);
		kern_return_t PerformBFH(char* bfhData, size_t bfhSize);
		kern_return_t SendNVMeCommand(uint32_t selector, const uint64_t* command, uint64_t commandSize);
		kern_return_t SetBFHMode(bool bfhMode);
		kern_return_t SetNVMeState(bool enableA, bool enableB);
		kern_return_t SetPCIPortState(bool A, bool B, uint32_t C);

	private:
		io_service_t svc;
		io_connect_t conn;

};