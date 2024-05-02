import argparse


def list_all_files(path):
    import glob
    return glob.glob(path + "/**/*Message.as", recursive=True)


def read_file(path):
    file = open(path, 'r')
    return file.read()


def find_packet_name(file_buffer):
    pos = file_buffer.find("   public class ")
    end_pos = file_buffer.find(" extends NetworkMessage")
    if end_pos == -1:
        return -1
    packet_name = file_buffer[pos + 16:end_pos]
    return packet_name


def find_packet_id(file_buffer):
    pos = file_buffer.find("protocolId:uint = ")
    packet_id = file_buffer[pos + 18:pos + 22]
    if packet_id[3] == ';':
        packet_id = packet_id[0:3]
    if packet_id[2] == ';':
        packet_id = packet_id[0:2]
    if packet_id[1] == ';':
        packet_id = packet_id[0:1]
    return packet_id


def loop(path):
    file_list = list_all_files(path)
    for file in file_list:
        file_content = read_file(file)
        name = find_packet_name(file_content)
        if name == -1:
            continue
        print("m_packet_names[" + find_packet_id(file_content) + "] = \"" + find_packet_name(file_content) + "\";")
    return 0


parser = argparse.ArgumentParser(prog='get_packets_id.py', description='Extracts packets ids')
parser.add_argument('path_to_dofus_scripts')
args = parser.parse_args()
loop(args.path_to_dofus_scripts)
