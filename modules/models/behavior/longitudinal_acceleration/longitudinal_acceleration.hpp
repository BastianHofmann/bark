// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef MODULES_MODELS_BEHAVIOR_LONGITUDINAL_ACCELERATION_LONGITUDINAL_ACCELERATION_HPP_
#define MODULES_MODELS_BEHAVIOR_LONGITUDINAL_ACCELERATION_LONGITUDINAL_ACCELERATION_HPP_

#include "modules/models/behavior/behavior_model.hpp"
#include "modules/world/world.hpp"

namespace modules {
namespace models {
namespace behavior {

using dynamic::Trajectory;
using world::objects::AgentId;
using world::ObservedWorld;

class BehaviorLongitudinalAcceleration : public BehaviorModel {
 public:
  explicit BehaviorLongitudinalAcceleration(commons::Params *params) :
    BehaviorModel(params) {}

  virtual ~BehaviorLongitudinalAcceleration() {}

  Trajectory Plan(float delta_time,
                 const ObservedWorld& observed_world);

  
  virtual double CalculateLongitudinalAcceleration(const ObservedWorld& observed_world) = 0;

  virtual BehaviorModel *Clone() const = 0;
};


}  // namespace behavior
}  // namespace models
}  // namespace modules

#endif  // MODULES_MODELS_BEHAVIOR_LONGITUDINAL_ACCELERATION_LONGITUDINAL_ACCELERATION_HPP_
