// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick
// Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include <limits>

#include "modules/models/behavior/motion_primitives/motion_primitives.hpp"
#include "modules/world/observed_world.hpp"

namespace modules {
namespace world {

using modules::geometry::Point2d;
using modules::models::behavior::BehaviorMotionPrimitives;
using modules::models::dynamic::State;
using modules::world::AgentMap;

FrontRearAgents ObservedWorld::GetAgentFrontRear() const {
  Point2d ego_pos = CurrentEgoPosition();
  const auto& road_corridor = GetRoadCorridor();
  BARK_EXPECT_TRUE(road_corridor != nullptr);
  const auto& lane_corridor = road_corridor->GetCurrentLaneCorridor(ego_pos);
  BARK_EXPECT_TRUE(lane_corridor != nullptr);

  AgentId id = GetEgoAgentId();
  FrontRearAgents fr_agent = GetAgentFrontRearForId(id, lane_corridor);

  return fr_agent;
}

AgentFrenetPair ObservedWorld::GetAgentInFront() const {
  FrontRearAgents fr_agent = GetAgentFrontRear();
  return fr_agent.front;
}

AgentFrenetPair ObservedWorld::GetAgentBehind() const {
  FrontRearAgents fr_agent = GetAgentFrontRear();
  return fr_agent.rear;
}

void ObservedWorld::SetupPrediction(const PredictionSettings& settings) {
  settings.ApplySettings(*this);
}

WorldPtr ObservedWorld::Predict(float time_span) const {
  std::shared_ptr<ObservedWorld> next_world =
      std::dynamic_pointer_cast<ObservedWorld>(ObservedWorld::Clone());
  next_world->Step(time_span);
  return std::dynamic_pointer_cast<World>(next_world);
}

WorldPtr ObservedWorld::Predict(float time_span,
                                const DiscreteAction& ego_action) const {
  std::shared_ptr<ObservedWorld> next_world =
      std::dynamic_pointer_cast<ObservedWorld>(ObservedWorld::Clone());
  std::shared_ptr<BehaviorMotionPrimitives> ego_behavior_model =
      std::dynamic_pointer_cast<BehaviorMotionPrimitives>(
          next_world->GetEgoBehaviorModel());
  if (ego_behavior_model) {
    ego_behavior_model->ActionToBehavior(ego_action);
  } else {
    LOG(ERROR) << "Currently only BehaviorMotionPrimitive model supported for "
                  "ego prediction, adjust prediction settings.";  // NOLINT
  }
  next_world->Step(time_span);
  return std::dynamic_pointer_cast<World>(next_world);
}

}  // namespace world
}  // namespace modules
