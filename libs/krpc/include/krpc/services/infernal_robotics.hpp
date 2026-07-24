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

class InfernalRobotics : public Service {
 public:
  explicit InfernalRobotics(Client* client);

  // Class forward declarations
  class Servo;
  class ServoGroup;

  /**
   * The mode a servo is operating in. See InfernalRobotics::Servo::mode.
   */
  enum struct ServoMode {
    /**
     * The part acts as a servo, driving towards a target position.
     */
    servo = 1,
    /**
     * The part acts as a rotor, spinning continuously.
     */
    rotor = 2
  };

  /**
   * Returns the servo group in the given vessel with the given name,
   * or null if none exists. If multiple servo groups have the same name, only one of them is returned.
   * @param vessel Vessel to check.
   * @param name Name of servo group to find.
   */
  InfernalRobotics::ServoGroup servo_group_with_name(SpaceCenter::Vessel vessel, std::string name);

  /**
   * A list of all the servo groups in the given vessel.
   *
   * Works for any loaded vessel, not just the active one. Groups on a non-active vessel
   * support movement and per-servo control, but not preset, key, speed-factor or
   * expanded state, which are only tracked by Infernal Robotics for the active vessel.
   */
  std::vector<InfernalRobotics::ServoGroup> servo_groups(SpaceCenter::Vessel vessel);

  /**
   * Returns the servo in the given vessel with the given name or
   * null if none exists. If multiple servos have the same name, only one of them is returned.
   * @param vessel Vessel to check.
   * @param name Name of the servo to find.
   */
  InfernalRobotics::Servo servo_with_name(SpaceCenter::Vessel vessel, std::string name);

  /**
   * Whether Infernal Robotics is installed.
   */
  bool available();

  /**
   * Whether Infernal Robotics API is ready.
   */
  bool ready();

  ::krpc::Stream<InfernalRobotics::ServoGroup> servo_group_with_name_stream(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::Stream<std::vector<InfernalRobotics::ServoGroup>> servo_groups_stream(SpaceCenter::Vessel vessel);

  ::krpc::Stream<InfernalRobotics::Servo> servo_with_name_stream(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::Stream<bool> available_stream();

  ::krpc::Stream<bool> ready_stream();

  ::krpc::schema::ProcedureCall servo_group_with_name_call(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::schema::ProcedureCall servo_groups_call(SpaceCenter::Vessel vessel);

  ::krpc::schema::ProcedureCall servo_with_name_call(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::schema::ProcedureCall available_call();

  ::krpc::schema::ProcedureCall ready_call();

  /**
   * Represents a servo. Obtained using
   * InfernalRobotics::ServoGroup::servos,
   * InfernalRobotics::ServoGroup::servo_with_name
   * or InfernalRobotics::servo_with_name.
   */
  class Servo : public krpc::Object<Servo> {
   public:
    explicit Servo(Client* client = nullptr, uint64_t id = 0);

    /**
     * Adds a preset position to the servo.
     * @param position The position of the preset.
     */
    void add_preset(float position);

    /**
     * Moves the servo to the center.
     */
    void move_center();

    /**
     * Moves the servo to the left.
     */
    void move_left();

    /**
     * Moves the servo to the right.
     */
    void move_right();

    /**
     * Moves the servo to position and sets the
     * speed multiplier to speed.
     * @param position The position to move the servo to.
     * @param speed Speed multiplier for the movement.
     */
    void move_to(float position, float speed);

    /**
     * Removes the preset position at the given index.
     * @param index The index of the preset to remove.
     */
    void remove_preset_at(int32_t index);

    /**
     * Sorts the preset positions of the servo into ascending order.
     */
    void sort_presets();

    /**
     * Stops the servo.
     */
    void stop();

    /**
     * The current speed multiplier set in the UI.
     */
    float acceleration();

    /**
     * The current speed multiplier set in the UI.
     */
    void set_acceleration(float value);

    /**
     * Whether the servo can have its range of movement limited.
     */
    bool can_have_limits();

    /**
     * The position the servo is currently being commanded to move to.
     */
    float commanded_position();

    /**
     * The speed multiplier of the servo, specified by the part configuration.
     */
    float config_speed();

    /**
     * The current speed at which the servo is moving.
     */
    float current_speed();

    /**
     * The strength of the servo's damping.
     */
    float damping_power();

    /**
     * The strength of the servo's damping.
     */
    void set_damping_power(float value);

    /**
     * The default (built) position of the servo.
     */
    float default_position();

    /**
     * The rate at which the servo consumes electric charge, in units per second, when moving.
     */
    float electric_charge_required();

    /**
     * The force limit of the servo, as a percentage of the maximum force.
     */
    float force_limit();

    /**
     * The force limit of the servo, as a percentage of the maximum force.
     */
    void set_force_limit(float value);

    /**
     * Whether the servo has a spring.
     */
    bool has_spring();

    /**
     * Whether the servo should be highlighted in-game.
     */
    void set_highlight(bool value);

    /**
     * Whether the servos axis is inverted.
     */
    bool is_axis_inverted();

    /**
     * Whether the servos axis is inverted.
     */
    void set_is_axis_inverted(bool value);

    /**
     * Whether the servo is freely moving.
     */
    bool is_free_moving();

    /**
     * Whether the servo's range of movement is limited to the configured minimum and
     * maximum positions.
     */
    bool is_limited();

    /**
     * Whether the servo's range of movement is limited to the configured minimum and
     * maximum positions.
     */
    void set_is_limited(bool value);

    /**
     * Whether the servo is locked.
     */
    bool is_locked();

    /**
     * Whether the servo is locked.
     */
    void set_is_locked(bool value);

    /**
     * Whether the servo is moving.
     */
    bool is_moving();

    /**
     * Whether the servo moves rotationally (as opposed to linearly).
     */
    bool is_rotational();

    /**
     * Whether the servo is running, when operating as a rotor.
     */
    bool is_running();

    /**
     * Whether the part is operating as a servo (rather than a rotor).
     */
    bool is_servo();

    /**
     * The maximum acceleration the servo can achieve.
     */
    float max_acceleration();

    /**
     * The maximum position of the servo, specified by the part configuration.
     */
    float max_config_position();

    /**
     * The maximum force the servo can generate.
     */
    float max_force();

    /**
     * The maximum position of the servo, specified by the in-game tweak menu.
     */
    float max_position();

    /**
     * The maximum position of the servo, specified by the in-game tweak menu.
     */
    void set_max_position(float value);

    /**
     * The maximum speed the servo can achieve.
     */
    float max_speed();

    /**
     * The minimum position of the servo, specified by the part configuration.
     */
    float min_config_position();

    /**
     * The minimum position of the servo, specified by the in-game tweak menu.
     */
    float min_position();

    /**
     * The minimum position of the servo, specified by the in-game tweak menu.
     */
    void set_min_position(float value);

    /**
     * Whether the part acts as a servo or a rotor.
     */
    InfernalRobotics::ServoMode mode();

    /**
     * The name of the servo.
     */
    std::string name();

    /**
     * The name of the servo.
     */
    void set_name(std::string value);

    /**
     * The part containing the servo.
     */
    SpaceCenter::Part part();

    /**
     * The position of the servo.
     */
    float position();

    /**
     * The list of preset positions configured for the servo.
     */
    std::vector<float> preset_positions();

    /**
     * The acceleration of the servo when operating as a rotor.
     */
    float rotor_acceleration();

    /**
     * The acceleration of the servo when operating as a rotor.
     */
    void set_rotor_acceleration(float value);

    /**
     * The speed multiplier of the servo, specified by the in-game tweak menu.
     */
    float speed();

    /**
     * The speed multiplier of the servo, specified by the in-game tweak menu.
     */
    void set_speed(float value);

    /**
     * The strength of the servo's spring, when it has one.
     */
    float spring_power();

    /**
     * The strength of the servo's spring, when it has one.
     */
    void set_spring_power(float value);

    /**
     * The target position the servo is moving towards.
     */
    float target_position();

    /**
     * The target speed the servo is moving at.
     */
    float target_speed();

    /**
     * The unique identifier of the servo.
     */
    uint32_t uid();

    ::krpc::Stream<float> acceleration_stream();

    ::krpc::Stream<bool> can_have_limits_stream();

    ::krpc::Stream<float> commanded_position_stream();

    ::krpc::Stream<float> config_speed_stream();

    ::krpc::Stream<float> current_speed_stream();

    ::krpc::Stream<float> damping_power_stream();

    ::krpc::Stream<float> default_position_stream();

    ::krpc::Stream<float> electric_charge_required_stream();

    ::krpc::Stream<float> force_limit_stream();

    ::krpc::Stream<bool> has_spring_stream();

    ::krpc::Stream<bool> is_axis_inverted_stream();

    ::krpc::Stream<bool> is_free_moving_stream();

    ::krpc::Stream<bool> is_limited_stream();

    ::krpc::Stream<bool> is_locked_stream();

    ::krpc::Stream<bool> is_moving_stream();

    ::krpc::Stream<bool> is_rotational_stream();

    ::krpc::Stream<bool> is_running_stream();

    ::krpc::Stream<bool> is_servo_stream();

    ::krpc::Stream<float> max_acceleration_stream();

    ::krpc::Stream<float> max_config_position_stream();

    ::krpc::Stream<float> max_force_stream();

    ::krpc::Stream<float> max_position_stream();

    ::krpc::Stream<float> max_speed_stream();

    ::krpc::Stream<float> min_config_position_stream();

    ::krpc::Stream<float> min_position_stream();

    ::krpc::Stream<InfernalRobotics::ServoMode> mode_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<float> position_stream();

    ::krpc::Stream<std::vector<float>> preset_positions_stream();

    ::krpc::Stream<float> rotor_acceleration_stream();

    ::krpc::Stream<float> speed_stream();

    ::krpc::Stream<float> spring_power_stream();

    ::krpc::Stream<float> target_position_stream();

    ::krpc::Stream<float> target_speed_stream();

    ::krpc::Stream<uint32_t> uid_stream();

    ::krpc::schema::ProcedureCall add_preset_call(float position);

    ::krpc::schema::ProcedureCall move_center_call();

    ::krpc::schema::ProcedureCall move_left_call();

    ::krpc::schema::ProcedureCall move_right_call();

    ::krpc::schema::ProcedureCall move_to_call(float position, float speed);

    ::krpc::schema::ProcedureCall remove_preset_at_call(int32_t index);

    ::krpc::schema::ProcedureCall sort_presets_call();

    ::krpc::schema::ProcedureCall stop_call();

    ::krpc::schema::ProcedureCall acceleration_call();

    ::krpc::schema::ProcedureCall set_acceleration_call(float value);

    ::krpc::schema::ProcedureCall can_have_limits_call();

    ::krpc::schema::ProcedureCall commanded_position_call();

    ::krpc::schema::ProcedureCall config_speed_call();

    ::krpc::schema::ProcedureCall current_speed_call();

    ::krpc::schema::ProcedureCall damping_power_call();

    ::krpc::schema::ProcedureCall set_damping_power_call(float value);

    ::krpc::schema::ProcedureCall default_position_call();

    ::krpc::schema::ProcedureCall electric_charge_required_call();

    ::krpc::schema::ProcedureCall force_limit_call();

    ::krpc::schema::ProcedureCall set_force_limit_call(float value);

    ::krpc::schema::ProcedureCall has_spring_call();

    ::krpc::schema::ProcedureCall set_highlight_call(bool value);

    ::krpc::schema::ProcedureCall is_axis_inverted_call();

    ::krpc::schema::ProcedureCall set_is_axis_inverted_call(bool value);

    ::krpc::schema::ProcedureCall is_free_moving_call();

    ::krpc::schema::ProcedureCall is_limited_call();

    ::krpc::schema::ProcedureCall set_is_limited_call(bool value);

    ::krpc::schema::ProcedureCall is_locked_call();

    ::krpc::schema::ProcedureCall set_is_locked_call(bool value);

    ::krpc::schema::ProcedureCall is_moving_call();

    ::krpc::schema::ProcedureCall is_rotational_call();

    ::krpc::schema::ProcedureCall is_running_call();

    ::krpc::schema::ProcedureCall is_servo_call();

    ::krpc::schema::ProcedureCall max_acceleration_call();

    ::krpc::schema::ProcedureCall max_config_position_call();

    ::krpc::schema::ProcedureCall max_force_call();

    ::krpc::schema::ProcedureCall max_position_call();

    ::krpc::schema::ProcedureCall set_max_position_call(float value);

    ::krpc::schema::ProcedureCall max_speed_call();

    ::krpc::schema::ProcedureCall min_config_position_call();

    ::krpc::schema::ProcedureCall min_position_call();

    ::krpc::schema::ProcedureCall set_min_position_call(float value);

    ::krpc::schema::ProcedureCall mode_call();

    ::krpc::schema::ProcedureCall name_call();

    ::krpc::schema::ProcedureCall set_name_call(std::string value);

    ::krpc::schema::ProcedureCall part_call();

    ::krpc::schema::ProcedureCall position_call();

    ::krpc::schema::ProcedureCall preset_positions_call();

    ::krpc::schema::ProcedureCall rotor_acceleration_call();

    ::krpc::schema::ProcedureCall set_rotor_acceleration_call(float value);

    ::krpc::schema::ProcedureCall speed_call();

    ::krpc::schema::ProcedureCall set_speed_call(float value);

    ::krpc::schema::ProcedureCall spring_power_call();

    ::krpc::schema::ProcedureCall set_spring_power_call(float value);

    ::krpc::schema::ProcedureCall target_position_call();

    ::krpc::schema::ProcedureCall target_speed_call();

    ::krpc::schema::ProcedureCall uid_call();
  };

  /**
   * A group of servos, obtained by calling InfernalRobotics::servo_groups
   * or InfernalRobotics::servo_group_with_name. Represents the "Servo Groups"
   * in the InfernalRobotics UI.
   */
  class ServoGroup : public krpc::Object<ServoGroup> {
   public:
    explicit ServoGroup(Client* client = nullptr, uint64_t id = 0);

    /**
     * Moves all of the servos in the group to the center.
     */
    void move_center();

    /**
     * Moves all of the servos in the group to the left.
     */
    void move_left();

    /**
     * Moves all of the servos in the group to the next preset.
     */
    void move_next_preset();

    /**
     * Moves all of the servos in the group to the previous preset.
     */
    void move_prev_preset();

    /**
     * Moves all of the servos in the group to the right.
     */
    void move_right();

    /**
     * Returns the servo with the given name from this group,
     * or null if none exists.
     * @param name Name of servo to find.
     */
    InfernalRobotics::Servo servo_with_name(std::string name);

    /**
     * Stops the servos in the group.
     */
    void stop();

    /**
     * Whether the group is in advanced mode.
     */
    bool advanced_mode();

    /**
     * Whether the group is in advanced mode.
     */
    void set_advanced_mode(bool value);

    /**
     * Whether the build aid is enabled for the group.
     */
    bool build_aid();

    /**
     * Whether the build aid is enabled for the group.
     */
    void set_build_aid(bool value);

    /**
     * The total rate at which the servos in the group consume electric charge, in units
     * per second, when moving.
     */
    float electric_charge_required();

    /**
     * Whether the group is expanded in the InfernalRobotics UI.
     */
    bool expanded();

    /**
     * Whether the group is expanded in the InfernalRobotics UI.
     */
    void set_expanded(bool value);

    /**
     * The key assigned to be the "forward" key for the group.
     */
    std::string forward_key();

    /**
     * The key assigned to be the "forward" key for the group.
     */
    void set_forward_key(std::string value);

    /**
     * Whether inverse kinematics is active for the group.
     */
    bool ik_active();

    /**
     * Whether inverse kinematics is active for the group.
     */
    void set_ik_active(bool value);

    /**
     * The direction the group is currently moving in: -1 for reverse, 0 for stopped
     * and 1 for forward.
     */
    int32_t moving_direction();

    /**
     * The name of the group.
     */
    std::string name();

    /**
     * The name of the group.
     */
    void set_name(std::string value);

    /**
     * The parts containing the servos in the group.
     */
    std::vector<SpaceCenter::Part> parts();

    /**
     * The key assigned to be the "reverse" key for the group.
     */
    std::string reverse_key();

    /**
     * The key assigned to be the "reverse" key for the group.
     */
    void set_reverse_key(std::string value);

    /**
     * The servos that are in the group.
     */
    std::vector<InfernalRobotics::Servo> servos();

    /**
     * The speed multiplier for the group.
     */
    float speed();

    /**
     * The speed multiplier for the group.
     */
    void set_speed(float value);

    /**
     * The vessel the group belongs to, or null if it is not available.
     */
    SpaceCenter::Vessel vessel();

    ::krpc::Stream<InfernalRobotics::Servo> servo_with_name_stream(std::string name);

    ::krpc::Stream<bool> advanced_mode_stream();

    ::krpc::Stream<bool> build_aid_stream();

    ::krpc::Stream<float> electric_charge_required_stream();

    ::krpc::Stream<bool> expanded_stream();

    ::krpc::Stream<std::string> forward_key_stream();

    ::krpc::Stream<bool> ik_active_stream();

    ::krpc::Stream<int32_t> moving_direction_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Part>> parts_stream();

    ::krpc::Stream<std::string> reverse_key_stream();

    ::krpc::Stream<std::vector<InfernalRobotics::Servo>> servos_stream();

    ::krpc::Stream<float> speed_stream();

    ::krpc::Stream<SpaceCenter::Vessel> vessel_stream();

    ::krpc::schema::ProcedureCall move_center_call();

    ::krpc::schema::ProcedureCall move_left_call();

    ::krpc::schema::ProcedureCall move_next_preset_call();

    ::krpc::schema::ProcedureCall move_prev_preset_call();

    ::krpc::schema::ProcedureCall move_right_call();

    ::krpc::schema::ProcedureCall servo_with_name_call(std::string name);

    ::krpc::schema::ProcedureCall stop_call();

    ::krpc::schema::ProcedureCall advanced_mode_call();

    ::krpc::schema::ProcedureCall set_advanced_mode_call(bool value);

    ::krpc::schema::ProcedureCall build_aid_call();

    ::krpc::schema::ProcedureCall set_build_aid_call(bool value);

    ::krpc::schema::ProcedureCall electric_charge_required_call();

    ::krpc::schema::ProcedureCall expanded_call();

    ::krpc::schema::ProcedureCall set_expanded_call(bool value);

    ::krpc::schema::ProcedureCall forward_key_call();

    ::krpc::schema::ProcedureCall set_forward_key_call(std::string value);

    ::krpc::schema::ProcedureCall ik_active_call();

    ::krpc::schema::ProcedureCall set_ik_active_call(bool value);

    ::krpc::schema::ProcedureCall moving_direction_call();

    ::krpc::schema::ProcedureCall name_call();

    ::krpc::schema::ProcedureCall set_name_call(std::string value);

    ::krpc::schema::ProcedureCall parts_call();

    ::krpc::schema::ProcedureCall reverse_key_call();

    ::krpc::schema::ProcedureCall set_reverse_key_call(std::string value);

    ::krpc::schema::ProcedureCall servos_call();

    ::krpc::schema::ProcedureCall speed_call();

    ::krpc::schema::ProcedureCall set_speed_call(float value);

    ::krpc::schema::ProcedureCall vessel_call();
  };
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::InfernalRobotics::ServoMode& value) {
    return krpc::encoder::encode(static_cast<int32_t>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::InfernalRobotics::ServoMode& value, const std::string& data, Client* client) {
    int32_t x;
    decode(x, data, client);
    value = static_cast<services::InfernalRobotics::ServoMode>(x);
  }

}  // namespace decoder

namespace services {

inline InfernalRobotics::InfernalRobotics(Client* client):
  Service(client) {
}

inline InfernalRobotics::ServoGroup InfernalRobotics::servo_group_with_name(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroupWithName", _args);
  InfernalRobotics::ServoGroup _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<InfernalRobotics::ServoGroup> InfernalRobotics::servo_groups(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroups", _args);
  std::vector<InfernalRobotics::ServoGroup> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline InfernalRobotics::Servo InfernalRobotics::servo_with_name(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoWithName", _args);
  InfernalRobotics::Servo _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::available() {
  std::string _data = this->_client->invoke("InfernalRobotics", "get_Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::ready() {
  std::string _data = this->_client->invoke("InfernalRobotics", "get_Ready");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<InfernalRobotics::ServoGroup> InfernalRobotics::servo_group_with_name_stream(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<InfernalRobotics::ServoGroup>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroupWithName", _args));
}

inline ::krpc::Stream<std::vector<InfernalRobotics::ServoGroup>> InfernalRobotics::servo_groups_stream(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  return ::krpc::Stream<std::vector<InfernalRobotics::ServoGroup>>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroups", _args));
}

inline ::krpc::Stream<InfernalRobotics::Servo> InfernalRobotics::servo_with_name_stream(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<InfernalRobotics::Servo>(this->_client, this->_client->build_call("InfernalRobotics", "ServoWithName", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "get_Available"));
}

inline ::krpc::Stream<bool> InfernalRobotics::ready_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "get_Ready"));
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::servo_group_with_name_call(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("InfernalRobotics", "ServoGroupWithName", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::servo_groups_call(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  return this->_client->build_call("InfernalRobotics", "ServoGroups", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::servo_with_name_call(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("InfernalRobotics", "ServoWithName", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::available_call() {
  return this->_client->build_call("InfernalRobotics", "get_Available");
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ready_call() {
  return this->_client->build_call("InfernalRobotics", "get_Ready");
}

inline InfernalRobotics::Servo::Servo(Client* client, uint64_t id):
  Object(client, "InfernalRobotics::Servo", id) {}

inline void InfernalRobotics::Servo::add_preset(float position) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(position));
  this->_client->invoke("InfernalRobotics", "Servo_AddPreset", _args);
}

inline void InfernalRobotics::Servo::move_center() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveCenter", _args);
}

inline void InfernalRobotics::Servo::move_left() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveLeft", _args);
}

inline void InfernalRobotics::Servo::move_right() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveRight", _args);
}

inline void InfernalRobotics::Servo::move_to(float position, float speed) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(speed));
  this->_client->invoke("InfernalRobotics", "Servo_MoveTo", _args);
}

inline void InfernalRobotics::Servo::remove_preset_at(int32_t index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  this->_client->invoke("InfernalRobotics", "Servo_RemovePresetAt", _args);
}

inline void InfernalRobotics::Servo::sort_presets() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_SortPresets", _args);
}

inline void InfernalRobotics::Servo::stop() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_Stop", _args);
}

inline float InfernalRobotics::Servo::acceleration() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Acceleration", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_acceleration(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Acceleration", _args);
}

inline bool InfernalRobotics::Servo::can_have_limits() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_CanHaveLimits", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::commanded_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_CommandedPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::config_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_ConfigSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::current_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_CurrentSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::damping_power() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_DampingPower", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_damping_power(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_DampingPower", _args);
}

inline float InfernalRobotics::Servo::default_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_DefaultPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::electric_charge_required() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_ElectricChargeRequired", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::force_limit() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_ForceLimit", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_force_limit(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_ForceLimit", _args);
}

inline bool InfernalRobotics::Servo::has_spring() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_HasSpring", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_highlight(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Highlight", _args);
}

inline bool InfernalRobotics::Servo::is_axis_inverted() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsAxisInverted", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_is_axis_inverted(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_IsAxisInverted", _args);
}

inline bool InfernalRobotics::Servo::is_free_moving() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsFreeMoving", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::Servo::is_limited() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsLimited", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_is_limited(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_IsLimited", _args);
}

inline bool InfernalRobotics::Servo::is_locked() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsLocked", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_is_locked(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_IsLocked", _args);
}

inline bool InfernalRobotics::Servo::is_moving() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsMoving", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::Servo::is_rotational() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsRotational", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::Servo::is_running() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsRunning", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::Servo::is_servo() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsServo", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::max_acceleration() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxAcceleration", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::max_config_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxConfigPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::max_force() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxForce", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::max_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_max_position(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_MaxPosition", _args);
}

inline float InfernalRobotics::Servo::max_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::min_config_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MinConfigPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::min_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MinPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_min_position(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_MinPosition", _args);
}

inline InfernalRobotics::ServoMode InfernalRobotics::Servo::mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Mode", _args);
  InfernalRobotics::ServoMode _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string InfernalRobotics::Servo::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Name", _args);
}

inline SpaceCenter::Part InfernalRobotics::Servo::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Position", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<float> InfernalRobotics::Servo::preset_positions() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_PresetPositions", _args);
  std::vector<float> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::rotor_acceleration() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_RotorAcceleration", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_rotor_acceleration(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_RotorAcceleration", _args);
}

inline float InfernalRobotics::Servo::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Speed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_speed(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Speed", _args);
}

inline float InfernalRobotics::Servo::spring_power() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_SpringPower", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_spring_power(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_SpringPower", _args);
}

inline float InfernalRobotics::Servo::target_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_TargetPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::target_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_TargetSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline uint32_t InfernalRobotics::Servo::uid() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_UID", _args);
  uint32_t _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::acceleration_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Acceleration", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::can_have_limits_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_CanHaveLimits", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::commanded_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_CommandedPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::config_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_ConfigSpeed", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::current_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_CurrentSpeed", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::damping_power_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_DampingPower", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::default_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_DefaultPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::electric_charge_required_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_ElectricChargeRequired", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::force_limit_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_ForceLimit", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::has_spring_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_HasSpring", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_axis_inverted_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsAxisInverted", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_free_moving_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsFreeMoving", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_limited_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsLimited", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_locked_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsLocked", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_moving_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsMoving", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_rotational_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsRotational", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_running_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsRunning", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_servo_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsServo", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_acceleration_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxAcceleration", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_config_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxConfigPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_force_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxForce", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxSpeed", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::min_config_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MinConfigPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::min_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MinPosition", _args));
}

inline ::krpc::Stream<InfernalRobotics::ServoMode> InfernalRobotics::Servo::mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<InfernalRobotics::ServoMode>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Mode", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::Servo::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Name", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> InfernalRobotics::Servo::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Part", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Position", _args));
}

inline ::krpc::Stream<std::vector<float>> InfernalRobotics::Servo::preset_positions_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<float>>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_PresetPositions", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::rotor_acceleration_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_RotorAcceleration", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Speed", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::spring_power_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_SpringPower", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::target_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_TargetPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::target_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_TargetSpeed", _args));
}

inline ::krpc::Stream<uint32_t> InfernalRobotics::Servo::uid_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<uint32_t>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_UID", _args));
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::add_preset_call(float position) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(position));
  return this->_client->build_call("InfernalRobotics", "Servo_AddPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_center_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveCenter", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_left_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveLeft", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_right_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveRight", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_to_call(float position, float speed) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(speed));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveTo", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::remove_preset_at_call(int32_t index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(index));
  return this->_client->build_call("InfernalRobotics", "Servo_RemovePresetAt", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::sort_presets_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_SortPresets", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::stop_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_Stop", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::acceleration_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Acceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_acceleration_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Acceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::can_have_limits_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_CanHaveLimits", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::commanded_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_CommandedPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::config_speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_ConfigSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::current_speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_CurrentSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::damping_power_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_DampingPower", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_damping_power_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_DampingPower", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::default_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_DefaultPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::electric_charge_required_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_ElectricChargeRequired", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::force_limit_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_ForceLimit", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_force_limit_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_ForceLimit", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::has_spring_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_HasSpring", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_highlight_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Highlight", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_axis_inverted_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsAxisInverted", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_is_axis_inverted_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_IsAxisInverted", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_free_moving_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsFreeMoving", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_limited_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsLimited", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_is_limited_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_IsLimited", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_locked_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsLocked", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_is_locked_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_IsLocked", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_moving_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsMoving", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_rotational_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsRotational", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_running_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsRunning", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_servo_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsServo", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_acceleration_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxAcceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_config_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxConfigPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_force_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxForce", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_max_position_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_MaxPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::min_config_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MinConfigPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::min_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MinPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_min_position_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_MinPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::mode_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Mode", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::name_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_name_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::part_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Part", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Position", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::preset_positions_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_PresetPositions", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::rotor_acceleration_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_RotorAcceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_rotor_acceleration_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_RotorAcceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Speed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_speed_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Speed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::spring_power_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_SpringPower", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_spring_power_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_SpringPower", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::target_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_TargetPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::target_speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_TargetSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::uid_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_UID", _args);
}

inline InfernalRobotics::ServoGroup::ServoGroup(Client* client, uint64_t id):
  Object(client, "InfernalRobotics::ServoGroup", id) {}

inline void InfernalRobotics::ServoGroup::move_center() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveCenter", _args);
}

inline void InfernalRobotics::ServoGroup::move_left() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveLeft", _args);
}

inline void InfernalRobotics::ServoGroup::move_next_preset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveNextPreset", _args);
}

inline void InfernalRobotics::ServoGroup::move_prev_preset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MovePrevPreset", _args);
}

inline void InfernalRobotics::ServoGroup::move_right() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveRight", _args);
}

inline InfernalRobotics::Servo InfernalRobotics::ServoGroup::servo_with_name(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_ServoWithName", _args);
  InfernalRobotics::Servo _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::stop() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_Stop", _args);
}

inline bool InfernalRobotics::ServoGroup::advanced_mode() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_AdvancedMode", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_advanced_mode(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_AdvancedMode", _args);
}

inline bool InfernalRobotics::ServoGroup::build_aid() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_BuildAid", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_build_aid(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_BuildAid", _args);
}

inline float InfernalRobotics::ServoGroup::electric_charge_required() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_ElectricChargeRequired", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::ServoGroup::expanded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Expanded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_expanded(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_Expanded", _args);
}

inline std::string InfernalRobotics::ServoGroup::forward_key() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_ForwardKey", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_forward_key(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_ForwardKey", _args);
}

inline bool InfernalRobotics::ServoGroup::ik_active() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_IKActive", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_ik_active(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_IKActive", _args);
}

inline int32_t InfernalRobotics::ServoGroup::moving_direction() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_MovingDirection", _args);
  int32_t _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string InfernalRobotics::ServoGroup::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_Name", _args);
}

inline std::vector<SpaceCenter::Part> InfernalRobotics::ServoGroup::parts() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Parts", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string InfernalRobotics::ServoGroup::reverse_key() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_ReverseKey", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_reverse_key(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_ReverseKey", _args);
}

inline std::vector<InfernalRobotics::Servo> InfernalRobotics::ServoGroup::servos() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Servos", _args);
  std::vector<InfernalRobotics::Servo> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::ServoGroup::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Speed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_speed(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_Speed", _args);
}

inline SpaceCenter::Vessel InfernalRobotics::ServoGroup::vessel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Vessel", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<InfernalRobotics::Servo> InfernalRobotics::ServoGroup::servo_with_name_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<InfernalRobotics::Servo>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_ServoWithName", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::ServoGroup::advanced_mode_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_AdvancedMode", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::ServoGroup::build_aid_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_BuildAid", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::ServoGroup::electric_charge_required_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_ElectricChargeRequired", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::ServoGroup::expanded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Expanded", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::ServoGroup::forward_key_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_ForwardKey", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::ServoGroup::ik_active_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_IKActive", _args));
}

inline ::krpc::Stream<int32_t> InfernalRobotics::ServoGroup::moving_direction_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<int32_t>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_MovingDirection", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::ServoGroup::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Name", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> InfernalRobotics::ServoGroup::parts_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Parts", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::ServoGroup::reverse_key_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_ReverseKey", _args));
}

inline ::krpc::Stream<std::vector<InfernalRobotics::Servo>> InfernalRobotics::ServoGroup::servos_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<InfernalRobotics::Servo>>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Servos", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::ServoGroup::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Speed", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> InfernalRobotics::ServoGroup::vessel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Vessel", _args));
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_center_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveCenter", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_left_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveLeft", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_next_preset_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveNextPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_prev_preset_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MovePrevPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_right_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveRight", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::servo_with_name_call(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_ServoWithName", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::stop_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_Stop", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::advanced_mode_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_AdvancedMode", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_advanced_mode_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_AdvancedMode", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::build_aid_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_BuildAid", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_build_aid_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_BuildAid", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::electric_charge_required_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_ElectricChargeRequired", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::expanded_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Expanded", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_expanded_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_Expanded", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::forward_key_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_ForwardKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_forward_key_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_ForwardKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::ik_active_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_IKActive", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_ik_active_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_IKActive", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::moving_direction_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_MovingDirection", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::name_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_name_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::parts_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Parts", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::reverse_key_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_ReverseKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_reverse_key_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_ReverseKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::servos_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Servos", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Speed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_speed_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_Speed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::vessel_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Vessel", _args);
}
}  // namespace services

}  // namespace krpc
