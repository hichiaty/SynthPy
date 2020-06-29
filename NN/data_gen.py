import SynthPy as sp
import numpy as np
import os
import matplotlib.pyplot as plt
from tqdm import tqdm
import gc


CHUNK_SIZE = 1000
TRAIN_SET_SIZE = 100000
TEST_SET_SIZE = 10000
TRAIN_SET_PATCH_DIR = 'Train_Patches'
TEST_SET_PATCH_DIR = 'Test_Patches'
PLUGIN_PATH = 'E:/VST/u-he/Diva.dll'


if not os.path.exists(TRAIN_SET_PATCH_DIR):
    os.makedirs(TRAIN_SET_PATCH_DIR)
if not os.path.exists(TEST_SET_PATCH_DIR):
    os.makedirs(TEST_SET_PATCH_DIR)    

# Generate Training Set
def gen_data(host, train=True):
    data_set = []
    generator = sp.PatchGenerator(host)

    for data_patch in tqdm(range(1,TRAIN_SET_SIZE+1)):

        patch = generator.get_random_patch()
        host.set_patch(patch)
        host.render_patch(72, 127, 1.0, 4.0)
        params = np.array([i[1] for i in patch])
        data_set.append(np.array([np.array(host.get_audio_frames()), params]))

        if data_patch % CHUNK_SIZE == 0:
            data_set = np.array(data_set)
            if train:
                with open(f'{TRAIN_SET_PATCH_DIR}/{data_patch}.spatch', 'wb') as f:
                    np.save(f, data_set)
            else:
                with open(f'{TEST_SET_PATCH_DIR}/{data_patch}.spatch', 'wb') as f:
                    np.save(f, data_set)
            data_set = []
            gc.collect()

if __name__ == '__main__':
    host = sp.Host(44100, 512, 512)

    if host.load_plugin(PLUGIN_PATH):
        print('Plugin Loaded!')
    
    # generate train:
    print('Generating training data...')
    gen_data(host)

    # gen test:
    print('Generating testing data...')
    gen_data(host, train=False)

    


