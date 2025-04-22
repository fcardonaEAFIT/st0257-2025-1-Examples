#!/usr/bin/env python
import click

def read_reqs_file(reqs_filename):
    result = []
    try:
        with open(reqs_filename, 'r') as reqsfile:
            for line in reqsfile:
                for e in line.split(' '):
                    req = int(e.strip())
                    result.append(req)
    except FileNotFoundError:
        print(f'File not found {reqs_filename}', file=sys.stderr)
        return None
    else:
        return result


def empty_frames(frames_size):
    for i in range(frames_size):
        yield None

def algo_fifo(frames_size,reqs):
    print("--- Replace pages FIFO ---")
    frames = [x for x in empty_frames(frames_size)]
    idx = 0; nrep = 0;
    for req in reqs:
        try:
            frames.index(req)
            print(f"req: {req} frames: ---")
        except ValueError:
            try:
                frames[frames.index(None)] = req
            except ValueError:
                frames[idx] = req
                idx = (idx + 1) % (frames_size)
                nrep = nrep + 1
            print(f"req: {req}  frames: {frames}")
    print(f"number of reqs: {len(reqs)} number of replace: {nrep}")

def algo_optimal(frames_size,reqs):
    def see_future(current_frames, next_reqs):
        max_offset = 0
        victim_frame = 0

        for idx in range(len(current_frames)):
            page = current_frames[idx]
            try:
                page_idx = next_reqs.index(page)
                if page_idx > max_offset:
                    max_offset = page_idx
                    victim_frame = idx
            except ValueError:
                victim_frame = idx
                break

        return victim_frame

    print("--- Replace pages Optimal ---")

    frames = [x for x in empty_frames(frames_size)]
    nrep = 0

    for idx in range(len(reqs)):
        req = reqs[idx]
        
        try:
            frames.index(req)
            print(f"req: {req} frames: ---")
        except ValueError:
            try:
                frames[frames.index(None)] = req
            except ValueError:
                frames[see_future(frames, reqs[idx+1:])] = req
                nrep = nrep + 1
            print(f"req: {req}  frames: {frames}")
    print(f"number of reqs: {len(reqs)} number of replace: {nrep}")

def algo_lru(frames_size,reqs):
    print("--- Replace pages LRU ---")
    lru = []
    def manlru(req):
        if req in lru:
            lru.pop(lru.index(req))
        lru.append(req)
    frames = [x for x in empty_frames(frames_size)]
    nrep = 0
    # lru = []
    for req in reqs:
        try:
            frames.index(req)
            manlru(req)
            print(f"req: {req} frames: ---")
        except ValueError:
            try:
                frames[frames.index(None)] = req
                manlru(req)
            except ValueError:
                victim_page = lru.pop(0)
                victim_frame  = frames.index(victim_page)
                frames[victim_frame] = req
                lru.append(req)
                nrep = nrep + 1
            print(f"req: {req} frames: {frames}")
    print(f"number of reqs: {len(reqs)} number of replace: {nrep}")

@click.command()
@click.option('--framesize', default='3', help='Number of Memory Frames (default=3)')
@click.option('--algo', default='fifo', help='Algorithm to execute fifo lru')
@click.option('--reqsfile', help='memory requirements file')
def process(framesize,algo, reqsfile):
    framesize=int(framesize)
    reqs= read_reqs_file(reqsfile)
    if reqs is None:
        return

    if algo == "fifo":
        algo_fifo(framesize,reqs)
    elif algo == "lru":
        algo_lru(framesize,reqs)
    elif algo == "optimal":
        algo_optimal(framesize,reqs)

if __name__ == '__main__':
    process()
