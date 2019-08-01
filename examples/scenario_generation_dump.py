# Copyright (c) 2019 fortiss GmbH
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT




from modules.runtime.scenario.scenario_generation.uniform_vehicle_distribution import UniformVehicleDistribution
from modules.runtime.commons.parameters import ParameterServer
from modules.runtime.viewer.pygame_viewer import PygameViewer
from modules.runtime.viewer.threaded_viewer import ThreadedViewer
import time
import os

scenario_param_file ="highway_merging.json" # must be within examples params folder

param_server = ParameterServer(filename= os.path.join("examples/params/",scenario_param_file))

scenario_generation = UniformVehicleDistribution(num_scenarios=3, random_seed=0, params=param_server)


renderer = PygameViewer(params=param_server, x_range=[-30,30], y_range=[-20,40], use_world_bounds=True)
viewer = ThreadedViewer(renderer=renderer, params=param_server)
viewer.start()

sim_step_time = param_server["simulation"]["step_time",
                                        "Step-time used in simulation",
                                        0.5]
sim_real_time_factor = param_server["simulation"]["real_time_factor",
                                                "execution in real-time or faster", 1]

for _ in range(0,2): # run 5 scenarios in a row, repeating after 3
    scenario, idx = scenario_generation.get_next_scenario()
    world_state = scenario.get_world_state()
    viewer.reset()
    print("Running scenario {} of {}".format(idx, scenario_generation.num_scenarios))
    for _ in range(0, 10): # run each scenario for 3 steps
        world_state.do_planning(sim_step_time)
        viewer.drawWorld(world_state)
        time.sleep(sim_step_time/sim_real_time_factor)
        world_state.do_execution(sim_step_time)

scenario_generation.dump_scenario_list(os.path.join("examples/scenarios/","{}_dump.bark_scenarios".format(os.path.splitext(scenario_param_file)[0])))