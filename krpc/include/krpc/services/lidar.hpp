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

class LiDAR : public Service {
 public:
  explicit LiDAR(Client* client);

  // Class forward declarations
  class Laser;

  /**
   * Get a LaserDist part.
   */
  LiDAR::Laser laser(SpaceCenter::Part part);

  /**
   * Check if the LaserDist API is available.
   */
  bool available();

  ::krpc::Stream<LiDAR::Laser> laser_stream(SpaceCenter::Part part);

  ::krpc::Stream<bool> available_stream();

  ::krpc::schema::ProcedureCall laser_call(SpaceCenter::Part part);

  ::krpc::schema::ProcedureCall available_call();

  /**
   * A LaserDist laser.
   */
  class Laser : public krpc::Object<Laser> {
   public:
    explicit Laser(Client* client = nullptr, uint64_t id = 0);

    /**
     * Get the point cloud from the LiDAR.
     * Returns an empty list on failure.
     */
    std::vector<double> cloud();

    /**
     * Get the part containing this LiDAR.
     */
    SpaceCenter::Part part();

    ::krpc::Stream<std::vector<double>> cloud_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::schema::ProcedureCall cloud_call();

    ::krpc::schema::ProcedureCall part_call();
  };
};

}  // namespace services

namespace services {

inline LiDAR::LiDAR(Client* client):
  Service(client) {
}

inline LiDAR::Laser LiDAR::laser(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  std::string _data = this->_client->invoke("LiDAR", "Laser", _args);
  LiDAR::Laser _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool LiDAR::available() {
  std::string _data = this->_client->invoke("LiDAR", "get_Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<LiDAR::Laser> LiDAR::laser_stream(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  return ::krpc::Stream<LiDAR::Laser>(this->_client, this->_client->build_call("LiDAR", "Laser", _args));
}

inline ::krpc::Stream<bool> LiDAR::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("LiDAR", "get_Available"));
}

inline ::krpc::schema::ProcedureCall LiDAR::laser_call(SpaceCenter::Part part) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(part));
  return this->_client->build_call("LiDAR", "Laser", _args);
}

inline ::krpc::schema::ProcedureCall LiDAR::available_call() {
  return this->_client->build_call("LiDAR", "get_Available");
}

inline LiDAR::Laser::Laser(Client* client, uint64_t id):
  Object(client, "LiDAR::Laser", id) {}

inline std::vector<double> LiDAR::Laser::cloud() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("LiDAR", "Laser_get_Cloud", _args);
  std::vector<double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Part LiDAR::Laser::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("LiDAR", "Laser_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<std::vector<double>> LiDAR::Laser::cloud_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<double>>(this->_client, this->_client->build_call("LiDAR", "Laser_get_Cloud", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> LiDAR::Laser::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->build_call("LiDAR", "Laser_get_Part", _args));
}

inline ::krpc::schema::ProcedureCall LiDAR::Laser::cloud_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("LiDAR", "Laser_get_Cloud", _args);
}

inline ::krpc::schema::ProcedureCall LiDAR::Laser::part_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("LiDAR", "Laser_get_Part", _args);
}
}  // namespace services

}  // namespace krpc
