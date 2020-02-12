# Copyright (c) 2020 fortiss GmbH
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT


import numpy as np

from modules.runtime.scenario.scenario_generation.config_readers.config_readers_interfaces import ConfigReaderControlledAgents

from bark.world.goal_definition import GoalDefinition, GoalDefinitionPolygon, GoalDefinitionStateLimits
from modules.runtime.commons.parameters import ParameterServer

# no one (in this road corridor) is a controlled agent
class NoneControlled(ConfigReaderControlledAgents):
   # returns list of size num agents with true or false depending if agent is controlled or not for each agent based on property, default_params_dict
  def create_from_config(self, config_param_object, road_corridor, agent_states,  **kwargs):
    return [False] * len(agent_states), {}, config_param_object

# Select one agent randomly as controlled agent
class RandomSingleAgent(ConfigReaderControlledAgents):
  # returns list of size num agents with true or false depending if agent is controlled or not for each agent based on property, default_params_dict
  def create_from_config(self, config_param_object, road_corridor, agent_states,  **kwargs):
    controlled_agent_idx = np.random.randint(low=0, high=len(agent_states), size=None)
    controlled_list = [False] * len(agent_states)
    controlled_list[controlled_agent_idx] = True
    return controlled_list, {}, config_param_object