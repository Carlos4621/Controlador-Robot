#include "ThermalCamera.h"

My::ThermalCamera::ThermalCamera(const uint8_t &slaveAddress) : slaveAddress_m{ slaveAddress } {
}

void My::ThermalCamera::updateCamera() {
    static std::array<uint16_t, 832> eeMLX90640;
    static std::array<uint16_t, 834> mlx90640Frame;

    paramsMLX90640 mlx90640;
    MLX90640_SetResolution(0x33, 0x03);
    
    MLX90640_DumpEE(slaveAddress_m, eeMLX90640.data());
    MLX90640_ExtractParameters(eeMLX90640.data(), &mlx90640);
    MLX90640_GetFrameData(0x33, mlx90640Frame.data());

    float tr{ MLX90640_GetTa(mlx90640Frame.data(), &mlx90640) - shift };

    MLX90640_CalculateTo(mlx90640Frame.data(), &mlx90640, emissivity, tr, lastImage_m.data());
}

std::array<float, 768> My::ThermalCamera::getImage() const noexcept {
    return lastImage_m;
}
