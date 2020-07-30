"""
 -*- coding: utf-8 -*-.

Created on Sun Oct 20 00:09:30 2019

@author: Varela
"""

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
        for per in range(2 ** 16 - 1, 0, -1):  # Period Range
            num = cnt / per
            if num.is_integer():
                return error, int(num), per, lead_cnt, trail_cnt
        error = 1
        return error, 0, 0, [0] * len(duty_cnt), [0] * len(duty_cnt)

    [err, loop_raw, period_count, lead_cnt, trail_cnt] = total_period()

    loop_num = loop_raw - 1
    return err, loop_num, period_count, lead_cnt, trail_cnt

# getClockValues(15000, [150.0, 200.0, 0.0, 0.0, 0.0, 0.0, 0.0], [200.0, 300.0, 0.0, 0.0, 0.0, 0.0, 0.0])