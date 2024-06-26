# Copyright 2024 TRAPS

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# イメージ引数設定
ARG BASE_IMAGE=humble-ros-base

# プラットフォームとベースのイメージを設定
FROM ros:${BASE_IMAGE}

# 設定されたワークスペースに移動
WORKDIR /root/ros2_ws

# ユーザー設定
USER root

# リポジトリとws_entry_point.shのコピー
COPY . "./src/package/."
ARG PACKAGE_NAME=$(xmllint --xpath "string(/package/name)" "./src/package/package.xml")
RUN mv "./src/package" "./src/${PACKAGE_NAME}"
COPY ./.docker/ws_entrypoint.sh /.
RUN chmod +x /ws_entrypoint.sh

# GitHub workfrowで実行時のリモート設定を削除
RUN sed -i '/\[http "https:\/\/github\.com\/"\]/,+1 d' ./src/${PACKAGE_NAME}/.git/config

# パッケージのインストール
RUN apt-get update && apt-get upgrade -y && xargs -a "./src/${PACKAGE_NAME}/config/apt/requirements.txt" apt-get install -y lsb-release wget software-properties-common gnupg
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 18
RUN rosdep update && rosdep install -iy --from-paths src
RUN rm ./llvm.sh && apt-get remove -y lsb-release wget software-properties-common gnupg
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# ビルド
RUN . /opt/ros/humble/setup.sh && colcon build --cmake-args -D CMAKE_C_COMPILER=clang-18 -D CMAKE_CXX_COMPILER=clang++-18
RUN rm -rf ./log

# .bashrcへの書き込み
RUN echo source $(pwd)/install/setup.bash >> ~/.bashrc

# 実行前に行われる操作
ENTRYPOINT ["/ws_entrypoint.sh"]

# 実行時のデフォルトのコマンド
CMD ["bash"]

WORKDIR /.