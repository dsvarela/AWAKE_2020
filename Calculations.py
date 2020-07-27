"""
 -*- coding: utf-8 -*-.

Created on Sun Oct 20 00:09:30 2019

@author: Varela
"""

milli_vec = [100, 131, 163, 204, 262, 327, 409, 511, 524, 655, 819, 1023, 1310,
             1638, 2047, 2621, 3276, 4095, 5242, 6553, 7242, 8191, 9207, 9828,
             10484, 11466, 12285, 13107, 14329, 14742, 15726, 16383, 17030,
             18347, 19659]

loop_vec = [125, 160, 200, 250, 320, 400, 500, 625, 640, 800, 1000, 1250, 1600,
            2000, 2500, 3200, 4000, 5000, 6400, 8000, 8875, 10000, 11250,
            12000, 12800, 14000, 15000, 16000, 17500, 18000, 19200, 20000,
            20800, 22400, 24000]


def getClockValues(millis, f_lead, f_duty):
    """Calculate Count Values From Input Times."""
    # Values For The Millis Counter
    cnt = int(millis * (10 ** 6) / 12.5)

    lead_cnt = [i / 12.5 for i in f_lead]
    duty_cnt = [i / 12.5 for i in f_duty]
    trail_cnt = []
    for i in range(0, len(duty_cnt)):
        trail_cnt.append(duty_cnt[i] + lead_cnt[i])

    for time in milli_vec:
        if millis <= time:
            idx = milli_vec.index(time) - 1
            break

    min_num = loop_vec[idx]

    def total_period():
        error = 0
        for num in range(min_num, 2 ** 16 + 1):  # Global Range
            for per in range(1, 2 ** 16):  # Period Range
                cnt_ = num * per
                if cnt_ == cnt:
                    return error, num, per, lead_cnt, trail_cnt
        error = 1
        return error, 0, 0, [0] * len(duty_cnt), [0] * len(duty_cnt)

    [err, loop_raw, period_count, lead_cnt, trail_cnt] = total_period()

    loop_num = loop_raw - 1
    return err, loop_num, period_count, lead_cnt, trail_cnt

# calc(1000, [100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0], [200.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])