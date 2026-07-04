#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <krpc/decoder.hpp>
#include <krpc/encoder.hpp>
#include <krpc/error.hpp>
#include <krpc/event.hpp>
#include <krpc/object.hpp>
#include <krpc/service.hpp>
#include <krpc/stream.hpp>

namespace krpc {
namespace services {

class DockingCamera : public Service {
 public:
  explicit DockingCamera(Client* client);

  // Class forward declarations
  class Camera;

  /**
   * Get a Camera part.
   */
  DockingCamera::Camera camera(SpaceCenter::Part part);

  /**
   * Check if the Camera API is available.
   */
  bool available();

  ::krpc::Stream<DockingCamera::Camera> camera_stream(SpaceCenter::Part part);

  ::krpc::Stream<bool> available_stream();

  ::krpc::schema::ProcedureCall camera_call(SpaceCenter::Part part);

  ::krpc::schema::ProcedureCall available_call();

  /**
   * A Docking Camera.
   */
  class Camera : public krpc::Object<Camera> {
   public:
    explicit Camera(Client* client = nullptr, uint64_t id = 0);

    /**
     * Get an image.
     * Returns an empty byte array on failure.
     */
    std::string image();

    /**
     * Get the part containing this camera.
     */
    SpaceCenter::Part part();

    ::krpc::Stream<std::string> image_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::schema::ProcedureCall image_call();

    ::krpc::schema::ProcedureCall part_call();
  };
};

}  // namespace services

namespace services {

inline DockingCamera::DockingCamera(Client* client):
  Service(client) {
}

inline DockingCamera::Camera DockingCamera::camera(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  std::string _data = this->_client->invoke("DockingCamera", "Camera", _args);
  DockingCamera::Camera _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool DockingCamera::available() {
  std::string _data = this->_client->invoke("DockingCamera", "get_Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<DockingCamera::Camera> DockingCamera::camera_stream(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  return ::krpc::Stream<DockingCamera::Camera>(this->_client, this->_client->build_call("DockingCamera", "Camera", _args));
}

inline ::krpc::Stream<bool> DockingCamera::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("DockingCamera", "get_Available"));
}

inline ::krpc::schema::ProcedureCall DockingCamera::camera_call(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  return this->_client->build_call("DockingCamera", "Camera", _args);
}

inline ::krpc::schema::ProcedureCall DockingCamera::available_call() {
  return this->_client->build_call("DockingCamera", "get_Available");
}

inline DockingCamera::Camera::Camera(Client* client, uint64_t id):
  Object(client, "DockingCamera::Camera", id) {}

inline std::string DockingCamera::Camera::image() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("DockingCamera", "Camera_get_Image", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part DockingCamera::Camera::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("DockingCamera", "Camera_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::string> DockingCamera::Camera::image_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("DockingCamera", "Camera_get_Image", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> DockingCamera::Camera::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->build_call("DockingCamera", "Camera_get_Part", _args));
}

inline ::krpc::schema::ProcedureCall DockingCamera::Camera::image_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("DockingCamera", "Camera_get_Image", _args);
}

inline ::krpc::schema::ProcedureCall DockingCamera::Camera::part_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("DockingCamera", "Camera_get_Part", _args);
}
}  // namespace services

}  // namespace krpc
