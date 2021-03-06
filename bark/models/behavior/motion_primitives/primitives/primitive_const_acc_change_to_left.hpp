// Copyright (c) 2020 fortiss GmbH
//
// Authors: Julian Bernhard, Klemens Esterle, Patrick Hart and
// Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef BARK_MODELS_BEHAVIOR_MOTION_PRIMITIVES_PRIMITIVES_PRIMITIVE_CONST_ACC_CHANGE_TO_LEFT_HPP_
#define BARK_MODELS_BEHAVIOR_MOTION_PRIMITIVES_PRIMITIVES_PRIMITIVE_CONST_ACC_CHANGE_TO_LEFT_HPP_

#include "bark/models/behavior/motion_primitives/primitives/primitive_const_acc_stay_lane.hpp"

namespace bark {
namespace models {
namespace behavior {
namespace primitives {

/**
 * @brief Change target corridor to the left with constant acceleration
 */
class PrimitiveConstAccChangeToLeft : public PrimitiveConstAccStayLane {
 public:
  explicit PrimitiveConstAccChangeToLeft(const commons::ParamsPtr& params);

  LaneCorridorPtr SelectTargetCorridor(
      const ObservedWorld& observed_world,
      const AdjacentLaneCorridors& adjacent_corridors) override;

  bool IsPreConditionSatisfied(
      const ObservedWorld& observed_world,
      const AdjacentLaneCorridors& adjacent_corridors) override;

  std::string GetName() const override;

 private:
  float min_length_;
};

}  // namespace primitives
}  // namespace behavior
}  // namespace models
}  // namespace bark

#endif  // BARK_MODELS_BEHAVIOR_MOTION_PRIMITIVES_PRIMITIVES_PRIMITIVE_CONST_ACC_CHANGE_TO_LEFT_HPP_
